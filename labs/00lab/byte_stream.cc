#include "byte_stream.hh"
#include <iostream>
using namespace std;


// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) {
    _capacity = capacity;
    _buffer.reserve(capacity);
}

size_t ByteStream::write(const string &data) {
    size_t remaining = _capacity - _occupied;
    size_t bytes = data.size() > remaining ? remaining : data.size();

    _buffer.append(data.substr(0, bytes));
    _occupied += bytes;
    _wrote += bytes;

    return bytes;
    //return {};
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return _buffer.substr(0, len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    _buffer.erase(0, len);
    _read += len;
    _occupied -= len;
    if (_buffer.size() == 0 && _input_ended) _eof = true;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    DUMMY_CODE(len);
    return {};
}

void ByteStream::end_input() {
    _input_ended = true;
    if (_buffer.size() == 0) 
        _eof = true;
}

bool ByteStream::input_ended() const { 
    return _input_ended; 
}

size_t ByteStream::buffer_size() const {
    return _buffer.size();
}

bool ByteStream::buffer_empty() const {
    if(_buffer.size() == 0)
        return true;
    else
        return false;
}

bool ByteStream::eof() const { 
    return _eof;
}

size_t ByteStream::bytes_written() const {
    return _wrote;
}

size_t ByteStream::bytes_read() const { 
    return _read;
}

size_t ByteStream::remaining_capacity() const { 
    return _capacity - _buffer.size();
}
