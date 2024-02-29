#include "document.h"
#include <iostream>

using namespace std;

Document::Document() = default;

Document::Document(int id, double relevance, int rating)
    : id(id)
        , relevance(relevance)
        , rating(rating) {
    }

ostream& operator<<(ostream& output, Document document) {
    output << "{ document_id = " << document.id << ", relevance = " << document.relevance
           << ", rating = " << document.rating << " }";

    return output;
}
