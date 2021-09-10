#ifndef _ILRD_RD743_BITS_ARRAY_HPP_
#define _ILRD_RD743_BITS_ARRAY_HPP_

#include <algorithm>
//#include <cstddef>
//#include <cstring>
#include <climits> // CHAR_BIT

#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)


namespace ilrd
{

class SumOfBits; // put on private of BitsArray
static const unsigned char LUT_bits_count[] = {COUNT_BITS}; // put on private of BitsArray
typedef unsigned long DWORD;// put on private of BitsArray
static const size_t bits_in_dword = CHAR_BIT * sizeof(DWORD);// put on private of BitsArray

template<size_t N>
class BitsArray
{
    class BitProxy;

public:
    explicit BitsArray();
    ~BitsArray();
    BitsArray(const BitsArray& other_);

    BitsArray& operator=(const BitsArray& other_);
    
    bool operator[](size_t idx_) const;
    BitProxy operator[](size_t idx_);
    
    BitsArray& operator>>=(size_t n_);
    BitsArray& operator<<=(size_t n_);

    BitsArray& operator&=(const BitsArray& other_);
    BitsArray& operator|=(const BitsArray& other_);
    BitsArray& operator^=(const BitsArray& other_);

    bool operator==(const BitsArray& other_) const;
    bool operator!=(const BitsArray& other_) const;

    void SetAll(bool val_ = true);
    size_t Count(bool val_ = true) const;

    BitsArray& ToggleAll();
    BitsArray& ToggleOne(size_t idx_);

    BitsArray& SetBit(size_t idx_, bool val_);
    bool GetBit(size_t idx_) const;

private:
    
    static const size_t n_elements = (N / bits_in_dword) + 
                                    (N % bits_in_dword != 0);
    DWORD m_arr[n_elements];

    class BitProxy
    {
    public:
        BitProxy(BitsArray& org_, size_t idx_);
        ~BitProxy();
        BitProxy& operator=(const BitProxy& rhs_);
        BitProxy& operator=(bool rhs_);
        operator bool() const;

    private:
        BitsArray& m_org;
        size_t m_idx;
    };

};

template<size_t N>
BitsArray<N>::BitProxy::BitProxy(BitsArray& org_, size_t idx_)
    : m_org(org_), m_idx(idx_)
{}

template<size_t N>
BitsArray<N>::BitProxy::~BitProxy()
{}

template<size_t N>
typename BitsArray<N>::BitProxy& BitsArray<N>::BitProxy::operator=(BitProxy& rhs_)
{
    m_org.SetBit(m_idx, rhs_.m_org.GetBit(rhs_.m_idx));

    return *this;
}

template<size_t N>
typename BitsArray<N>::BitProxy& BitsArray<N>::BitProxy::operator=(bool rhs_)
{
    m_org.SetBit(m_idx, rhs_);

    return *this;
}

template<size_t N>
BitsArray<N>::BitProxy::operator bool() const
{
    return m_org.GetBit(m_idx);
}

template<size_t N>
BitsArray<N>::BitsArray()
    : m_arr()
{}

template<size_t N>
BitsArray<N>::~BitsArray()
{}

template<size_t N>
BitsArray<N>::BitsArray(const BitsArray& other_)
    : m_arr()
{
    std::copy(other_.m_arr, other_.m_arr + n_elements, m_arr);
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator=(const BitsArray& other_)
{
    std::copy(m_arr, m_arr + n_elements, other_.m_arr);
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator&=(const BitsArray& other_)
{
    std::transform(m_arr, m_arr + n_elements, other_.m_arr, m_arr, std::bit_and<DWORD>());

    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator|=(const BitsArray& other_)
{
    std::transform(m_arr, m_arr + n_elements, other_.m_arr, m_arr, std::bit_or<DWORD>());

    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator^=(const BitsArray& other_)
{
    std::transform(m_arr, m_arr + n_elements, other_.m_arr, m_arr, std::bit_xor<DWORD>());

    return *this;
}

template<size_t N>
bool BitsArray<N>::operator==(const BitsArray& other_) const
{
    return std::equal(m_arr, m_arr + n_elements, other_.m_arr);
}

template<size_t N>
bool BitsArray<N>::operator!=(const BitsArray& other_) const
{
    return (std::mismatch(m_arr, m_arr + n_elements, other_.m_arr)).first != m_arr + n_elements;
}

template<size_t N>
void BitsArray<N>::SetAll(bool val_)
{
    std::fill(m_arr, m_arr + n_elements, ~(DWORD)val_ + 1);
}

template<size_t N>
BitsArray<N>& BitsArray<N>::ToggleAll()
{
    BitsArray<N> mask;
    mask.SetAll();

    *this ^= mask;

    return *this;
}

template<size_t N>
bool BitsArray<N>::operator[](size_t idx_) const
{
    return GetBit(idx_);
}

template<size_t N>
typename BitsArray<N>::BitProxy BitsArray<N>::operator[](size_t idx_)
{
    return BitsArray<N>::BitProxy(*this, idx_);
}

class SumOfBits
{
public:
    SumOfBits() : sum(0) {}

    void operator() (DWORD cur_element)
    {
        for (unsigned int i = 0; i < sizeof(DWORD); ++i)
        {
            sum += LUT_bits_count[static_cast<unsigned char>(cur_element >> i * CHAR_BIT)];
        }
    }

    size_t sum;
};

template<size_t N>
size_t BitsArray<N>::Count(bool val_) const
{
    SumOfBits Sum = std::for_each(m_arr, m_arr + n_elements, SumOfBits());

    if (val_ == false)
    {
        return (n_elements * bits_in_dword - Sum.sum);
    }

    return Sum.sum;
}


template<size_t N>
BitsArray<N>& BitsArray<N>::ToggleOne(size_t idx_)
{
    m_arr[idx_ / bits_in_dword] ^= (1UL << (idx_ % bits_in_dword));

    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::SetBit(size_t idx_, bool val_)
{
    if (GetBit(idx_) != val_)
    {
        ToggleOne(idx_);
    }

    return *this;
}

template<size_t N>
bool BitsArray<N>::GetBit(size_t idx_) const
{
    return (m_arr[idx_ / bits_in_dword] & 
            1UL << (idx_ % bits_in_dword)) != 0;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator>>=(size_t n_)
{}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator<<=(size_t n_)
{}

} // namespace ILRD

#endif