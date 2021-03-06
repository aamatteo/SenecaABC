/* ------------------------------------------------------------------ */
/*      item            : AudioObjectMotion.cxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "AudioObjectMotion.hxx"
#include <iostream>
#include <cassert>
#if !defined(__DCO_NOPACK)
#include <AmorphStore.hxx>
#include <PackUnpackTemplates.hxx>
#endif
#include <DataWriterArraySize.hxx>
#define DOBS(A)
#if !defined(__DCO_STANDALONE)
#include <Arena.hxx>
#include <ArenaPool.hxx>
#include <DataClassRegistrar.hxx>
#include <CommObjectMemberAccess.hxx>
#include <DCOFunctor.hxx>
#include <DCOMetaFunctor.hxx>

#define DO_INSTANTIATE
#include <DataSetSubsidiary.hxx>
#endif
#ifdef DUECA_CONFIG_HDF5
#include <hdf5utils/HDF5Templates.hxx>
#endif




#if !defined(__DCO_STANDALONE)
// static CommObjectMemberAccess objects, that can provide flexible access
// to the members of a AudioObjectMotion object
static ::dueca::CommObjectMemberAccess
  <AudioObjectMotion,float >
  AudioObjectMotion_member_volume(&AudioObjectMotion::volume, "volume");
static ::dueca::CommObjectMemberAccess
  <AudioObjectMotion,float >
  AudioObjectMotion_member_pitch(&AudioObjectMotion::pitch, "pitch");

// assemble the above entries into a table in the order in which they
// appear in the AudioObjectMotion object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &AudioObjectMotion_member_volume },
  { &AudioObjectMotion_member_pitch },
  { NULL }
};

#endif

// class name, static
const char * const AudioObjectMotion::classname = "AudioObjectMotion";

// magic number, hashed from class name and member names / classes
const uint32_t AudioObjectMotion::magic_check_number=0x96f84663;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (AudioObjectMotion::classname, BaseObjectMotion::classname,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<AudioObjectMotion>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
AudioObjectMotion::AudioObjectMotion():
    volume(0.0f),
    pitch(1.0f)
{
  DOBS("default constructor AudioObjectMotion");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
AudioObjectMotion::AudioObjectMotion(
        const BaseObjectMotion& parent_BaseObjectMotion,
        const float& volume,
        const float& pitch) :
        BaseObjectMotion(parent_BaseObjectMotion),
    volume(volume),
    pitch(pitch)
{
  DOBS("complete constructor AudioObjectMotion");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
AudioObjectMotion::AudioObjectMotion(
        const float& volume,
        const float& pitch) :
    volume(volume),
    pitch(pitch)
{
  DOBS("complete single argument constructor AudioObjectMotion");
}
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
AudioObjectMotion::AudioObjectMotion(const AudioObjectMotion& other):
        BaseObjectMotion(other),
    volume(other.volume),
    pitch(other.pitch)
{
  DOBS("copy constructor AudioObjectMotion");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
AudioObjectMotion::AudioObjectMotion(dueca::AmorphReStore& s):
        BaseObjectMotion(s),
        volume(s),
        pitch(s)
{
  DOBS("amorph constructor AudioObjectMotion");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
AudioObjectMotion::~AudioObjectMotion()
{
  DOBS("destructor AudioObjectMotion");
}
#endif

#if !defined(__DCO_STANDALONE)
void* AudioObjectMotion::operator new(size_t size)
{
  DOBS("operator new AudioObjectMotion");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(AudioObjectMotion));
  return my_arena->alloc(size);
}

void AudioObjectMotion::operator delete(void* v)
{
  DOBS("operator delete AudioObjectMotion");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(AudioObjectMotion));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void AudioObjectMotion::packDataDiff(::dueca::AmorphStore& s, const AudioObjectMotion& ref) const
{
  DOBS("packDataDiff AudioObjectMotion");
  ::dueca::IndexMemory im;
        this->BaseObjectMotion::packDataDiff(s, ref);
  ::dueca::checkandpackdiffsingle(this->volume, ref.volume,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->pitch, ref.pitch,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void AudioObjectMotion::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData AudioObjectMotion");

        this->BaseObjectMotion::unPackData(s);
  ::unPackData(s, this->volume);
  ::unPackData(s, this->pitch);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void AudioObjectMotion::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff AudioObjectMotion");
  ::dueca::IndexRecall im;
        this->BaseObjectMotion::unPackDataDiff(s);
  ::dueca::checkandunpackdiffsingle(this->volume, s, im);
  ::dueca::checkandunpackdiffsingle(this->pitch, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool AudioObjectMotion::operator == (const AudioObjectMotion& other) const
{
  DOBS("operator == AudioObjectMotion");
  if (this->BaseObjectMotion::operator != (other)) return false;
  if (this->volume != other.volume) return false;
  if (this->pitch != other.pitch) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
AudioObjectMotion&
AudioObjectMotion::operator=(const AudioObjectMotion& other)
{
  DOBS("operator = AudioObjectMotion");
  if (this == &other) return *this;
        this->BaseObjectMotion::operator=(other);
  this->volume = other.volume;
  this->pitch = other.pitch;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void AudioObjectMotion::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData AudioObjectMotion");
        this->BaseObjectMotion::packData(s);
  ::packData(s, this->volume);
  ::packData(s, this->pitch);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & AudioObjectMotion::print(std::ostream& s) const
{
  s << "AudioObjectMotion(";
  this->BaseObjectMotion::print(s);
  s
    << "volume=" << this->volume << ','
    << "pitch=" << this->pitch
    << ')';
  return s;
}
#endif


#if defined(DUECA_CONFIG_HDF5)
// guarded in a separate namespace
namespace AudioObjectMotion_space {

#if !defined(__CUSTOM_HDF5_WRITE_FUNCTOR)
  HDF5DCOWriteFunctor::
  HDF5DCOWriteFunctor(boost::weak_ptr<H5::H5File> file,
                      const std::string& path,
                      size_t chunksize,
                      const std::string& label,
                      bool compress, bool writeticks,
                      const dueca::DataTimeSpec* startend) :
    dueca::hdf5log::HDF5DCOWriteFunctor(file, path, chunksize, label,
                               2, compress, writeticks,
                               startend),
    __parent__(file, path + std::string("/__parent__"), chunksize,
               std::string(""), compress, false, startend)
  {
    // add memspaces for all elements

    this->configureDataSet(0, "/data/volume",
                           HOFFSET(AudioObjectMotion, volume),
                           dueca::get_hdf5_elt_type(example.volume),
                           dueca::get_hdf5_elt_length(example.volume));

    this->configureDataSet(1, "/data/pitch",
                           HOFFSET(AudioObjectMotion, pitch),
                           dueca::get_hdf5_elt_type(example.pitch),
                           dueca::get_hdf5_elt_length(example.pitch));

    if (writeticks) {
      dueca::TimeTickType tex;
      this->configureDataSet(2, "/tick", 0,
                             dueca::get_hdf5_elt_type(tex), 1);
    }
  }

  // the functor member used by channel reading code, writes data in HDF5 file
  bool HDF5DCOWriteFunctor::operator() (const void* dpointer,
                                        const dueca::DataTimeSpec& ts)
  {
    while (ts.getValidityEnd() <= startend->getValidityStart()) {
      return true;
    }
    if (ts.getValidityStart() >= startend->getValidityEnd()) {
      return false;
    }
      __parent__.operator() (dpointer, ts);
    this->prepareRow();

    this->sets[0].writeNew(dpointer, chunkidx, example.volume);

    this->sets[1].writeNew(dpointer, chunkidx, example.pitch);

    if (writeticks) {
      this->sets[2].writeNew(&ts);
    }
    return true;
  }
#endif


#if !defined(__CUSTOM_HDF5_READ_FUNCTOR)
  HDF5DCOReadFunctor::
  HDF5DCOReadFunctor(boost::weak_ptr<H5::H5File> file,
                     const std::string& path,
                     bool readticks) :
    dueca::hdf5log::HDF5DCOReadFunctor(file, path,
                              2, readticks),
    __parent__(file, path + std::string("__parent__"), false)
  {
    // add memspaces for all elements

    this->configureDataSet(0, "/data/volume",
                           HOFFSET(AudioObjectMotion, volume),
                           dueca::get_hdf5_elt_type(example.volume),
                           dueca::get_hdf5_elt_length(example.volume));

    this->configureDataSet(1, "/data/pitch",
                           HOFFSET(AudioObjectMotion, pitch),
                           dueca::get_hdf5_elt_type(example.pitch),
                           dueca::get_hdf5_elt_length(example.pitch));

    if (readticks) {
      dueca::TimeTickType tex;
      this->configureDataSet(2, "/tick", 0,
                             dueca::get_hdf5_elt_type(tex), 1);
    }
  }

  bool HDF5DCOReadFunctor::operator() (void* dpointer)
  {

    __parent__.operator() (dpointer);
    this->sets[0].readObjectPart(dpointer, example.volume);

    this->sets[1].readObjectPart(dpointer, example.pitch);

    return true;
  }
#endif


  /** Metafunctor, can be accessed through the table, and can
      produce a functor object and the HDF5 data type */
  class HDF5DCOMetaFunctor: public dueca::hdf5log::HDF5DCOMetaFunctor
  {
    HDF5DCOWriteFunctor* getWriteFunctor(boost::weak_ptr<H5::H5File> file,
                                         const std::string& path,
                                         size_t chunksize,
                                         const std::string& label,
                                         const dueca::DataTimeSpec* startend,
                                         bool compress,
                                         bool writeticks=true)
    {
      return new HDF5DCOWriteFunctor(file, path, chunksize, label,
                                     compress, writeticks, startend);
    }

    HDF5DCOReadFunctor* getReadFunctor(boost::weak_ptr<H5::H5File> file,
                                       const std::string& path,
                                       bool writeticks=true)
    {
      return new HDF5DCOReadFunctor(file, path, writeticks);
    }

  };

#if !defined(__DCO_STANDALONE)
  // loads the metafunctor in the table
  static dueca::LoadMetaFunctor<HDF5DCOMetaFunctor>
    load_functor(functortable, "hdf5");
#endif
} // end namespace AudioObjectMotion_space
#endif

