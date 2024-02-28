#pragma once
#include <algorithm>
#include <iostream>

using namespace std;

template <typename Iterator>
struct Page {
    Iterator start_page;
    Iterator end_page;
};

template <typename Iterator>
class Paginator {
public:

    Paginator() = default;

    explicit Paginator(Iterator begin, Iterator stop, size_t page_size){
        while(begin != stop){
            Page<Iterator> new_page;

            new_page.start_page = begin;

            size_t remaining_size = distance(begin, stop);
            if(remaining_size >= page_size){
                begin = next(begin, page_size);
                new_page.end_page = begin;
            }else{
                begin = next(begin, remaining_size);
                new_page.end_page = begin;
            }

            _pages.emplace_back(new_page);
        }
    }

    auto begin() const {
        return _pages.begin();
    }

    auto end() const {
        return _pages.end();
    }

    size_t size(){
        return _pages.size();
    }

private:
    vector<Page<Iterator>> _pages;
};

ostream& operator<<(ostream& output, Document document) {
    output << "{ document_id = " << document.id << ", relevance = " << document.relevance
           << ", rating = " << document.rating << " }";

    return output;
}

template <typename Iterator>
ostream& operator<<(ostream& output, Page<Iterator> page) {
    while (page.start_page != page.end_page){
        output << *page.start_page;
        page.start_page= next(page.start_page, 1);
    }

    return output;
}

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}