#pragma once
//http://www.drdobbs.com/cpp/c-view-objects/196513737?pgno=3
#include <vector>
#include <iterator>
#include <algorithm>

namespace OK::View
{
    namespace detail
    {

    template<typename ContainerType>
    class view_element
    {
    protected:
        typedef typename ContainerType::value_type value_type;
        typename ContainerType::const_iterator _iterator;
    public:
        inline const value_type& value() const {
            return *_iterator;
        }


        view_element(typename ContainerType::const_iterator it) : _iterator{ it } {}
    };

    }

template<typename ContainerType>
class view
{
protected:
    typedef detail::view_element<ContainerType> element_type;
    typedef typename ContainerType::value_type value_type;
    std::vector<element_type> _elements;
public:
    value_type operator[] (size_t i) { return _elements[i].value(); }

    typedef typename std::vector<element_type>::iterator iterator;

    inline void add(element_type it) { _elements.emplace_back(it); }

    view() = default;
    view(const ContainerType& container) {
        std::for_each(container.begin(),s)
    }
};

}