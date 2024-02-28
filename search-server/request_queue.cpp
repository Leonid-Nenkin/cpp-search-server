#include "request_queue.h"
#include <algorithm>

using namespace std;

    RequestQueue::RequestQueue(const SearchServer& search_server): search_server_(search_server) {
    }
    
    template <typename DocumentPredicate>
    vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentPredicate document_predicate) {
        auto result = search_server_.FindTopDocuments(raw_query, document_predicate);
        AddRequestResult(result.empty());
        return result;
    }
    vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentStatus status) {
        auto result = search_server_.FindTopDocuments(raw_query, status);
        AddRequestResult(result.empty());
        return result;
    }
    vector<Document> RequestQueue::AddFindRequest(const string& raw_query) {
        auto result = search_server_.FindTopDocuments(raw_query, DocumentStatus::ACTUAL);
        AddRequestResult(result.empty());
        return result;
    }
    int RequestQueue::GetNoResultRequests() const {
        return count_if(requests_.begin(), requests_.end(), [](const QueryResult& result) {
            return result.empty;
        });
    }
    
    void RequestQueue::AddRequestResult(bool empty) {
        requests_.emplace_back(QueryResult{empty});
        if (requests_.size() > min_in_day_) {
            requests_.pop_front();
        }
    }
    