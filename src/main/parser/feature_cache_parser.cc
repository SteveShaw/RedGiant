#include "parser/feature_cache_parser.h"

#include <string>
#include "utils/logger.h"

namespace redgiant {

DECLARE_LOGGER(logger, __FILE__);

int FeatureCacheParser::parse_json(const rapidjson::Value& root, FeatureCache& output) {
  for (auto it = root.Begin(); it != root.End(); ++it) {
    int id;
    std::string name;
    std::string type;
    if (!it->HasMember("id") || !(*it)["id"].IsInt()) {
      LOG_ERROR(logger, "feature spaces does not contain valid id!");
      return -1;
    }
    id = (*it)["id"].GetInt();

    if (!it->HasMember("name") || !(*it)["name"].IsString()) {
      LOG_ERROR(logger, "feature spaces does not contain valid id!");
      return -1;
    }
    name = (*it)["name"].GetString();

    if (!it->HasMember("type") || !(*it)["type"].IsString()) {
      LOG_ERROR(logger, "feature spaces does not contain valid id!");
      return -1;
    }
    type = (*it)["type"].GetString();

    output.create_space(name, (FeatureSpace::SpaceId)id,
        type == "string" ? FeatureSpace::kString : FeatureSpace::kInteger);
  }
  return 0;
}

} /* namespace redgiant */
