#pragma once
#include "search_server.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    
    template <typename DocumentPredicate>
    vector<Document> AddFindRequest(const string& raw_query, DocumentPredicate document_predicate);
    vector<Document> AddFindRequest(const string& raw_query, DocumentStatus status);
    vector<Document> AddFindRequest(const string& raw_query);
    int GetNoResultRequests() const;

    private:
    struct QueryResult {
        bool empty;
    };
    
    void AddRequestResult(bool empty);
    
    const SearchServer& search_server_;
    deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;

};