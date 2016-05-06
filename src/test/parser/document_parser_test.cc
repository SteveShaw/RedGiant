#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "model/document.h"
#include "model/feature_cache.h"
#include "model/feature_vector.h"
#include "parser/document_parser.h"

using namespace std;

namespace redgiant {
class DocumentParserTest: public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(DocumentParserTest);
  CPPUNIT_TEST(test_parser);
  CPPUNIT_TEST(test_parser_withoutuuid);
  CPPUNIT_TEST_SUITE_END();

public:
  DocumentParserTest() = default;
  virtual ~DocumentParserTest() = default;

protected:
  void test_parser() {
    auto cache = create_cache();
    auto parser = create_parser(cache.get());

    string s =
      R"({
        "uuid": "abcd1234-9876-1234-ffff-001122ddeeff",
        "features": {
          "publisher": "publisher_id_test",
          "time": "1234567",
          "categories": {"1": 0.1, "2":0.2, "3" : 0.3}, 
          "entities": {"ent_1":0.1, "ent_2":0.2, "ent_3" : 0.3},
          "unknown": "abc"
        }
      })";

    Document doc;
    int ret = parser->parse(s.c_str(), s.length(), doc);

    CPPUNIT_ASSERT_EQUAL(0, ret);
    // check doc meta
    CPPUNIT_ASSERT_EQUAL(string("abcd1234-9876-1234-ffff-001122ddeeff"), doc.get_id_str());
    CPPUNIT_ASSERT_EQUAL(string("abcd1234-9876-1234-ffff-001122ddeeff"), doc.get_id().to_string());

    const auto& vecs = doc.get_feature_vectors();
    CPPUNIT_ASSERT_EQUAL(4, (int)vecs.size());

    // feature vector 1: publisher
    auto fv = &(vecs[0]);
    CPPUNIT_ASSERT_EQUAL(string("publisher"), fv->get_space_name());
    CPPUNIT_ASSERT_EQUAL(FeatureSpace::kString, fv->get_space()->get_type());
    // only one item
    CPPUNIT_ASSERT_EQUAL(1, (int)fv->get_features().size());
    auto f = &(fv->get_features()[0]);
    CPPUNIT_ASSERT_EQUAL(string("publisher_id_test"), f->first->get_key());
    CPPUNIT_ASSERT_DOUBLES_EQUAL((double)1.0, f->second, 0.0001);

    fv = &(vecs[1]);
    CPPUNIT_ASSERT_EQUAL(string("time"), fv->get_space_name());
    CPPUNIT_ASSERT_EQUAL(FeatureSpace::kInteger, fv->get_space()->get_type());
    // only one item
    CPPUNIT_ASSERT_EQUAL(1, (int)fv->get_features().size());
    f = &(fv->get_features()[0]);
    CPPUNIT_ASSERT_EQUAL(string("1234567"), f->first->get_key());
    CPPUNIT_ASSERT_DOUBLES_EQUAL((double)1.0, f->second, 0.0001);

    fv = &(vecs[2]);
    CPPUNIT_ASSERT_EQUAL(string("categories"), fv->get_space_name());
    CPPUNIT_ASSERT_EQUAL(FeatureSpace::kInteger, fv->get_space()->get_type());
    // 3 items
    CPPUNIT_ASSERT_EQUAL(3, (int)fv->get_features().size());
    f = &(fv->get_features()[0]);
    CPPUNIT_ASSERT_EQUAL(string("1"), f->first->get_key());
    CPPUNIT_ASSERT_DOUBLES_EQUAL((double)0.1, f->second, 0.0001);
    f = &(fv->get_features()[1]);
    CPPUNIT_ASSERT_EQUAL(string("2"), f->first->get_key());
    CPPUNIT_ASSERT_DOUBLES_EQUAL((double)0.2, f->second, 0.0001);
    f = &(fv->get_features()[2]);
    CPPUNIT_ASSERT_EQUAL(string("3"), f->first->get_key());
    CPPUNIT_ASSERT_DOUBLES_EQUAL((double)0.3, f->second, 0.0001);

    fv = &(vecs[3]);
    CPPUNIT_ASSERT_EQUAL(string("entities"), fv->get_space_name());
    CPPUNIT_ASSERT_EQUAL(FeatureSpace::kString, fv->get_space()->get_type());
    // 3 items
    CPPUNIT_ASSERT_EQUAL(3, (int)fv->get_features().size());
    f = &(fv->get_features()[0]);
    CPPUNIT_ASSERT_EQUAL(string("ent_1"), f->first->get_key());
    CPPUNIT_ASSERT_DOUBLES_EQUAL((double)0.1, f->second, 0.0001);
    f = &(fv->get_features()[1]);
    CPPUNIT_ASSERT_EQUAL(string("ent_2"), f->first->get_key());
    CPPUNIT_ASSERT_DOUBLES_EQUAL((double)0.2, f->second, 0.0001);
    f = &(fv->get_features()[2]);
    CPPUNIT_ASSERT_EQUAL(string("ent_3"), f->first->get_key());
    CPPUNIT_ASSERT_DOUBLES_EQUAL((double)0.3, f->second, 0.0001);
  }

  void test_parser_withoutuuid() {
    auto cache = create_cache();
    auto parser = create_parser(cache.get());

    string s =
      R"({
        "features": {
          "publisher": "publisher_id_test",
          "time": "1234567",
          "categories": {"1": 0.1, "2":0.2, "3" : 0.3}, 
          "entities": {"ent_1":0.1, "ent_2":0.2, "ent_3" : 0.3},
          "unknown": "abc"
        }
      })";

    Document doc;
    int ret = parser->parse(s.c_str(), s.length(), doc);
    CPPUNIT_ASSERT_EQUAL(-1, ret);
  }

private:
  std::unique_ptr<FeatureCache> create_cache() {
    auto cache = std::unique_ptr<FeatureCache>(new FeatureCache());
    cache->create_space("time", 1, FeatureSpace::FeatureType::kInteger);
    cache->create_space("publisher", 2, FeatureSpace::FeatureType::kString);
    cache->create_space("entities", 3, FeatureSpace::FeatureType::kString);
    cache->create_space("categories", 3, FeatureSpace::FeatureType::kInteger);
    return cache;
  };

  std::unique_ptr<DocumentParser> create_parser(FeatureCache* cache) {
    return std::unique_ptr<DocumentParser>(new DocumentParser(cache));
  };
};

CPPUNIT_TEST_SUITE_REGISTRATION(DocumentParserTest);
} /* namespace redgiant */