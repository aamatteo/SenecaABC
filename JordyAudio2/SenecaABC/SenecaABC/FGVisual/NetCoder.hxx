//************************************************************
// Endian.hpp
//
// Created on Tue Apr  5 13:42:07 2011 by Jan Comans
//
// Copyright 2011 Jan Comans -- jan@comans.be
//
// Licensed under the Academic Free License version 3.0
// http://www.opensource.org/licenses/afl-3.0.php
//************************************************************

#ifndef __NETCODER_HXX__
#define __NETCODER_HXX__

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>


namespace Endian
{
  /// The different byte orders we can handle at this point.
  /// Internally, only little and big endian are used
  enum byte_order
  { little_endian, big_endian, host_order, network_order };

  /// Determine the byte order of the machine we are working on
  inline byte_order host_byte_order()
  {
    // Store a number which is zero everywhere except for the
    // 1 bit.
    short int word = 0x0001;

    // Look at the int as if it was a char. This provides
    // access to the individual bits
    char*     byte = reinterpret_cast<char*>(&word);

    // If 1 was stored as 0001 0000, the machine is little endian
    // If 1 was stored as 0000 0001, the machine is big endian
    return byte[0] ? little_endian:big_endian ;
  }

  /// The actual byte swapping function to convert between
  /// little and big endian
  ///\param data A pointer to the data that need to be swapped
  ///\param n The number of bytes occupied by the provided data
  inline void byte_swap(char* data, size_t n)
  {
    size_t i=0;
    size_t j=n-1;

    // Changing endianess is conceptually the same as
    // mirroring around the 'middle' bit
    while(i<j)
    {
      std::swap(data[i],data[j]);
      ++i; --j;
    }
  }

  /// The class that takes care of encoding the data into
  /// a buffer with a specific endianess
  class Encoder
  {
  public:
    /// Create a new encoder. Data storage in the encoder is
    /// based on a vector, it will dynamically increase its size
    /// if necesary. However, most of the time the size of the
    /// buffer is known beforehand and it is recomended to
    /// provide the constructor with a size to preallocate the
    /// memory
    ///\param size The size of the buffer managed by the encoder
    ///\param bo The byte order in which the data will be stored
    /// in the buffer
    Encoder(size_t size=32, byte_order bo=network_order):
      _buffer(),
      _host_byte_order(host_byte_order()),
      _data_byte_order(bo)
    {
      /// Preallocate some memory
      _buffer.reserve(size);
      
      // Internaly we only use big or little endian
      if(_data_byte_order == network_order)
	_data_byte_order = big_endian;
      if(_data_byte_order == host_order)
	_data_byte_order = _host_byte_order;
    }

    /// Low level encoding function. Add a chunk of data to the
    /// buffer and swap the bytes if necesary to get the correct
    /// endianess in the buffer. This function can be used directly,
    /// but it is recomended to use operator<< instead.
    ///\param chunk A pointer to the data that need to be encoded
    ///\param size The size of the data that need to be encoded
    ///\param swap Flag to indicate if swapping is necesary. For
    /// example, if the chunk consists of a char array, no swapping
    /// is necesary.
    void encode(const char* chunk, size_t size, bool swap=true)
    {
      // We are inserting multiple chars, so we use insert instead
      // of push_back
      _buffer.insert(_buffer.end(),chunk, chunk+size);

      // Only swap when necesary
      if(swap &&
	 _host_byte_order != _data_byte_order)
      {
	byte_swap(&(_buffer[_buffer.size() - size]), size);
      }
    }

    /// Provide direct access to the data inside the encoder.
    /// The data can't be modified in this way. This function
    /// alows functions that require a pointer to a data array
    /// to use an encoder object.
    const char* data() const
    {
      return &(_buffer[0]);
    }

    /// Return the size of the encoder object
    size_t size() const { return _buffer.size(); }

    /// Clear the data and reset the encoder
    void clear()
    {
      size_t size = _buffer.size();
      _buffer.clear();
      
      // Clearing shouldn't relaese memory, but just to make
      // sure, reserve the required size
      _buffer.reserve(size);
    }
    
  private:
    typedef std::vector<char> buffer_t;
    
    buffer_t         _buffer;
    const byte_order _host_byte_order;
    byte_order       _data_byte_order;    
  };

  /// Insertion operator to facilitate adding data
  /// to an encoder. This operator takes care of calling the
  /// low level encode function with the right parameters.
  template<typename T>
  inline Encoder& operator<<(Encoder& encoder, const T& data)
  {
    encoder.encode( reinterpret_cast<const char*>(&data), sizeof(T) );
    return encoder;
  }

  /// A specialization of the insertion operator for strings.
  /// Strings do not need to be swapped, they are inserted 'as is'.
  template<>
  inline Encoder& operator<<(Encoder& encoder, const std::string& data)
  {
    encoder.encode( data.c_str(), data.size(), false );
    return encoder;
  }

  /// Insertion operator for standard C strings. They are required
  /// to be zero terminated. Character arrarys that are not zero
  /// terminated should be inserted by calling the encode function
  /// directly
  inline Encoder& operator<<(Encoder& encoder, const char* data)
  {
    encoder.encode( data, strlen(data), false );
    return encoder;
  }


  /// The class that takes care of decoding a data buffer
  /// with a specific endianess. The only way data can be
  /// added to a decoder is by copying data into it using
  /// the data pointer provided by the data() function.
  /// It is up to the user to allocate enough room during
  /// construction. 
  class Decoder
  {
  public:
    /// Create a decoder with a given size.
    ///\param size The size of the buffer that needs to be allocated
    ///\param bo The byte order of the data that will be stored
    Decoder(size_t size, byte_order bo=network_order):
      _buffer(size),
      _received_size(size),
      _index(0),
      _host_byte_order(host_byte_order()),
      _data_byte_order(bo)
    {
      // Internaly we only use big or little endian
      if(_data_byte_order == network_order)
	_data_byte_order = big_endian;
      if(_data_byte_order == host_order)
	_data_byte_order = _host_byte_order;
    }

    /// Low level decoding function, prefer operator>>
    /// Return a poiner to a chunk of decoded bits. Depending
    /// on the byte order, the bits will be swapped to put them
    /// into machine order again.
    /// Data can only be read once. Each call to decode will
    /// increment the internal data pointer to point to the next
    /// chunk of data
    const char* decode(size_t size, bool swap=true)
    {
      // Something is wrong when more bits are requested than
      // stored in the buffer
      if( size > this->received_size())
	throw -1;

      // Swap if necesary. Data are swapped in the buffer.
      if(swap &&
	 _host_byte_order != _data_byte_order)
      {
	byte_swap( &(_buffer[_index]), size);
      }

      // Increase the data pointer
      _index += size;

      // Return a pointer to the data which are now in
      // host byte order
      return &(_buffer[_index-size]);
    }

    /// Provide access to the buffer. This pointer needs to be
    /// used to fill the Decoder. It is inted to be used with
    /// legacy C functions that require a char or void pointer
    char* data() { return &(_buffer[0]); }

    /// When less data are received than the size of the underlying
    /// storage, the size should be passed to avoid reading
    /// uninitialized data
    void received_size(size_t size)
    {
      if(size > _buffer.size())
	throw -3;

      _received_size = size;
    }

    /// The amount of usefull data in the encoder. Always larger or
    /// equal than the size
    size_t received_size() const
    {
      return _received_size;
    }

    /// The size of the valid data left in the buffer. Decoding
    /// data will decrease the size.
    size_t size() const
    {
      return _received_size - _index;
    }

    /// The raw size of the underlying buffer, not constrained by
    /// the received amount of data. When the decoder is reset,
    /// it is reset to this value.
    size_t storage_size()
    {
      return _buffer.size();
    }

    /// Clear the receiving buffer
    void clear()
    {
      size_t size = _buffer.size();
      _buffer.clear();
      _buffer.resize(size);

      _received_size = size;
      _index = 0;
    }

  private:
    typedef std::vector<char> buffer_t;
    
    buffer_t         _buffer;
    size_t           _received_size;
    size_t           _index;
    const byte_order _host_byte_order;
    byte_order       _data_byte_order;    
  };

  /// Extraction operator to facilitate decoding data from a
  /// Decoder object. This function will take care of calling the
  /// decode function with the right parameters
  template<typename T>
  inline Decoder& operator>>(Decoder& decoder, T& data)
  {
    data = *( reinterpret_cast<const T*>(decoder.decode(sizeof(T)))  );
    return decoder;
  }

  /// Extraction operator specialized for std::string. The
  /// goal is to facilitate decoding char data/arrays.
  /// The function will decode a number of chars from the encoder
  /// without swapping. The amount of chars is determined by the
  /// string size. The actual data inside the string are irrelevant
  /// and will be overwritten by this function
  template<>
  inline Decoder& operator>> <std::string> (Decoder& decoder,
				     std::string& data)
  {
    const char* buf = decoder.decode(data.size(),false);

    data = std::string(buf, data.size());
    return decoder;
  }
};

#endif // __NETCODER_HXX__
