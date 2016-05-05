#ifndef SRC_MAIN_INDEX_DOCUMENT_QUERY_H_
#define SRC_MAIN_INDEX_DOCUMENT_QUERY_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "core/query/posting_list_query.h"
#include "index/document_index.h"
#include "index/document_traits.h"
#include "model/query_request.h"

namespace redgiant {
class QueryRequest;

class DocumentQuery {
public:
  typedef double Score;
  typedef typename DocumentIndex::Query<Score> DocQuery;
  typedef typename DocumentIndex::QueryPair<Score> DocQueryPair;
  typedef typename DocumentIndex::Results<Score> Results;

  DocumentQuery(const QueryRequest& request);
  ~DocumentQuery() = default;

  size_t get_query_count() const {
    return query_count_;
  }

  const std::vector<DocQueryPair>& get_doc_queries() const {
    return doc_queries_;
  }

private:
  size_t query_count_;
  std::vector<DocQueryPair> doc_queries_;
};
} /* namespace redgiant */

#endif /* SRC_MAIN_INDEX_DOCUMENT_QUERY_H_ */
