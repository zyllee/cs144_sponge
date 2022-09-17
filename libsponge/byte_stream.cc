#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : _capacity(capacity) {}

// Write a string of bytes into the stream. Write as many 
// as will fit, and return the number of bytes written.
size_t ByteStream::write(const string &data) {
    size_t length = data.size();
    if(length > _capacity - _buffer.size())
        length = _capacity - _buffer.size();
    _write_cnt += length;
    for(size_t i = 0;i < length;++i)
        _buffer.push_back(data[i]);
    return length;
}

//! \param[in] len bytes will be copied from the output side of the buffer
// Peek at next "len" bytes of the stream 
string ByteStream::peek_output(const size_t len) const {
    size_t length = len;
    if( length > _buffer.size() )
        length = _buffer.size();
    return string().assign(_buffer.begin(),_buffer.begin() + length );
}

//! \param[in] len bytes will be removed from the output side of the buffer
// Remove "len" bytes from the buffer
void ByteStream::pop_output(const size_t len) {
    size_t length = len;
    if(length > _buffer.size())
        length = _buffer.size();
    _read_cnt += length;
    for(size_t i = 0;i < length;i++)
        _buffer.pop_front();
    //length = 0;
    return ;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
// Read (i.e., copy and then pop) the next "len" bytes of the stream 
std::string ByteStream::read(const size_t len) {
    size_t length = len;
    std::string read_string{};
    if(length > _buffer.size())
        length = _buffer.size();
    for(size_t i = 0;i < length;i++){
        read_string.push_back(_buffer[i]);
        _buffer.pop_front();
    }
    _read_cnt += length;
    return read_string;
}

// Signal that the byte stream has reached its ending 
void ByteStream::end_input() {_input_ended_flag = true;}
// `true` if the stream input has ended 
bool ByteStream::input_ended() const { return _input_ended_flag; }
// the maximum amount that can currently be peeked/read
size_t ByteStream::buffer_size() const { return _buffer.size(); }
// `true` if the buffer is empty
bool ByteStream::buffer_empty() const { return _buffer.empty(); }
// `true` if the output has reached the ending
bool ByteStream::eof() const { return buffer_empty() && input_ended(); }
// Total number of bytes written
size_t ByteStream::bytes_written() const { return _write_cnt; }
// Total number of bytes popped
size_t ByteStream::bytes_read() const { return _read_cnt; }
// Returns the number of additional bytes that the stream has space for
size_t ByteStream::remaining_capacity() const { return _capacity - _buffer.size(); }
