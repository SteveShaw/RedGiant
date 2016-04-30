#include "pipeline/feed_document_pipeline.h"

#include <utility>
#include "utils/logger.h"

namespace redgiant {

DECLARE_LOGGER(logger, __FILE__);

FeedDocumentPipeline::FeedDocumentPipeline(size_t thread_num, size_t queue_size) {
  feed_document_ = std::make_shared<WorkerExecutor<FeedDocumentJob, FeedDocumentWorker>>(
      std::make_shared<FeedDocumentWorkerFactory>(), thread_num, queue_size);
}

void FeedDocumentPipeline::start() {
  feed_document_->start();
}

void FeedDocumentPipeline::stop() {
  feed_document_->stop();
}

void FeedDocumentPipeline::schedule(std::shared_ptr<FeedDocumentJob> job) {
  feed_document_->schedule(std::move(job));
  LOG_TRACE(logger, "job pushed, queue size: %zu", feed_document_->get_queue_size());
}

} /* namespace redgiant */
