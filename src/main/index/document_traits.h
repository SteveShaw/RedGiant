#ifndef SRC_MAIN_INDEX_DOCUMENT_TRAITS_H_
#define SRC_MAIN_INDEX_DOCUMENT_TRAITS_H_

#include <functional>
#include "model/document.h"
#include "model/document_id.h"
#include "model/feature.h"
#include "model/feature_vector.h"

namespace redgiant {
class DocumentTraits {
public:
  typedef Document Doc;
  typedef DocumentId DocId;
  typedef Feature::FeatureId TermId;
  typedef FeatureVector::Weight TermWeight;
  typedef int32_t ExpireTime;
  typedef double Score;
  typedef DocumentId::Hash DocIdHash;
  typedef std::hash<TermId> TermIdHash;
};
} /* namespace redgiant */

#endif /* SRC_MAIN_INDEX_DOCUMENT_TRAITS_H_ */
