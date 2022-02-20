/* ------------------------------------------------------------------ */
/*      item            : SecondaryControls.cxx
        generated by    : matteo (matteo)
        date            : Wed 15 Dec 2021
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "SecondaryControls.hxx"
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
// to the members of a SecondaryControls object
static ::dueca::CommObjectMemberAccess
  <SecondaryControls,float >
  SecondaryControls_member_throttle_left(&SecondaryControls::throttle_left, "throttle_left");
static ::dueca::CommObjectMemberAccess
  <SecondaryControls,float >
  SecondaryControls_member_throttle_right(&SecondaryControls::throttle_right, "throttle_right");
static ::dueca::CommObjectMemberAccess
  <SecondaryControls,float >
  SecondaryControls_member_flap_setting(&SecondaryControls::flap_setting, "flap_setting");
static ::dueca::CommObjectMemberAccess
  <SecondaryControls,float >
  SecondaryControls_member_speedbrake(&SecondaryControls::speedbrake, "speedbrake");

// assemble the above entries into a table in the order in which they
// appear in the SecondaryControls object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &SecondaryControls_member_throttle_left },
  { &SecondaryControls_member_throttle_right },
  { &SecondaryControls_member_flap_setting },
  { &SecondaryControls_member_speedbrake },
  { NULL }
};

#endif

// class name, static
const char * const SecondaryControls::classname = "SecondaryControls";

// magic number, hashed from class name and member names / classes
const uint32_t SecondaryControls::magic_check_number=0xa7017af8;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (SecondaryControls::classname, NULL,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<SecondaryControls>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
SecondaryControls::SecondaryControls():
    throttle_left(0.0f),
    throttle_right(0.0f),
    flap_setting(0.0f),
    speedbrake(0.0f)
{
  DOBS("default constructor SecondaryControls");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
SecondaryControls::SecondaryControls(
        const float& throttle_left,
        const float& throttle_right,
        const float& flap_setting,
        const float& speedbrake) :
    throttle_left(throttle_left),
    throttle_right(throttle_right),
    flap_setting(flap_setting),
    speedbrake(speedbrake)
{
  DOBS("complete constructor SecondaryControls");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
SecondaryControls::SecondaryControls(const SecondaryControls& other):
    throttle_left(other.throttle_left),
    throttle_right(other.throttle_right),
    flap_setting(other.flap_setting),
    speedbrake(other.speedbrake)
{
  DOBS("copy constructor SecondaryControls");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
SecondaryControls::SecondaryControls(dueca::AmorphReStore& s):
        throttle_left(s),
        throttle_right(s),
        flap_setting(s),
        speedbrake(s)
{
  DOBS("amorph constructor SecondaryControls");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
SecondaryControls::~SecondaryControls()
{
  DOBS("destructor SecondaryControls");
}
#endif

#if !defined(__DCO_STANDALONE)
void* SecondaryControls::operator new(size_t size)
{
  DOBS("operator new SecondaryControls");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(SecondaryControls));
  return my_arena->alloc(size);
}

void SecondaryControls::operator delete(void* v)
{
  DOBS("operator delete SecondaryControls");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(SecondaryControls));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void SecondaryControls::packDataDiff(::dueca::AmorphStore& s, const SecondaryControls& ref) const
{
  DOBS("packDataDiff SecondaryControls");
  ::dueca::IndexMemory im;
  ::dueca::checkandpackdiffsingle(this->throttle_left, ref.throttle_left,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->throttle_right, ref.throttle_right,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->flap_setting, ref.flap_setting,
                         s, im);
  ::dueca::checkandpackdiffsingle(this->speedbrake, ref.speedbrake,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void SecondaryControls::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData SecondaryControls");

  ::unPackData(s, this->throttle_left);
  ::unPackData(s, this->throttle_right);
  ::unPackData(s, this->flap_setting);
  ::unPackData(s, this->speedbrake);

}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void SecondaryControls::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff SecondaryControls");
  ::dueca::IndexRecall im;
  ::dueca::checkandunpackdiffsingle(this->throttle_left, s, im);
  ::dueca::checkandunpackdiffsingle(this->throttle_right, s, im);
  ::dueca::checkandunpackdiffsingle(this->flap_setting, s, im);
  ::dueca::checkandunpackdiffsingle(this->speedbrake, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool SecondaryControls::operator == (const SecondaryControls& other) const
{
  DOBS("operator == SecondaryControls");
  if (this->throttle_left != other.throttle_left) return false;
  if (this->throttle_right != other.throttle_right) return false;
  if (this->flap_setting != other.flap_setting) return false;
  if (this->speedbrake != other.speedbrake) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
SecondaryControls&
SecondaryControls::operator=(const SecondaryControls& other)
{
  DOBS("operator = SecondaryControls");
  if (this == &other) return *this;
  this->throttle_left = other.throttle_left;
  this->throttle_right = other.throttle_right;
  this->flap_setting = other.flap_setting;
  this->speedbrake = other.speedbrake;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void SecondaryControls::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData SecondaryControls");
  ::packData(s, this->throttle_left);
  ::packData(s, this->throttle_right);
  ::packData(s, this->flap_setting);
  ::packData(s, this->speedbrake);
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & SecondaryControls::print(std::ostream& s) const
{
  s << "SecondaryControls("
    << "throttle_left=" << this->throttle_left << ','
    << "throttle_right=" << this->throttle_right << ','
    << "flap_setting=" << this->flap_setting << ','
    << "speedbrake=" << this->speedbrake
    << ')';
  return s;
}
#endif


#if defined(DUECA_CONFIG_HDF5)
// guarded in a separate namespace
namespace SecondaryControls_space {

#if !defined(__CUSTOM_HDF5_WRITE_FUNCTOR)
  HDF5DCOWriteFunctor::
  HDF5DCOWriteFunctor(boost::weak_ptr<H5::H5File> file,
                      const std::string& path,
                      size_t chunksize,
                      const std::string& label,
                      bool compress, bool writeticks,
                      const dueca::DataTimeSpec* startend) :
    dueca::hdf5log::HDF5DCOWriteFunctor(file, path, chunksize, label,
                               4, compress, writeticks,
                               startend)
  {
    // add memspaces for all elements

    this->configureDataSet(0, "/data/throttle_left",
                           HOFFSET(SecondaryControls, throttle_left),
                           dueca::get_hdf5_elt_type(example.throttle_left),
                           dueca::get_hdf5_elt_length(example.throttle_left));

    this->configureDataSet(1, "/data/throttle_right",
                           HOFFSET(SecondaryControls, throttle_right),
                           dueca::get_hdf5_elt_type(example.throttle_right),
                           dueca::get_hdf5_elt_length(example.throttle_right));

    this->configureDataSet(2, "/data/flap_setting",
                           HOFFSET(SecondaryControls, flap_setting),
                           dueca::get_hdf5_elt_type(example.flap_setting),
                           dueca::get_hdf5_elt_length(example.flap_setting));

    this->configureDataSet(3, "/data/speedbrake",
                           HOFFSET(SecondaryControls, speedbrake),
                           dueca::get_hdf5_elt_type(example.speedbrake),
                           dueca::get_hdf5_elt_length(example.speedbrake));

    if (writeticks) {
      dueca::TimeTickType tex;
      this->configureDataSet(4, "/tick", 0,
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
    this->prepareRow();

    this->sets[0].writeNew(dpointer, chunkidx, example.throttle_left);

    this->sets[1].writeNew(dpointer, chunkidx, example.throttle_right);

    this->sets[2].writeNew(dpointer, chunkidx, example.flap_setting);

    this->sets[3].writeNew(dpointer, chunkidx, example.speedbrake);

    if (writeticks) {
      this->sets[4].writeNew(&ts);
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
                              4, readticks)
  {
    // add memspaces for all elements

    this->configureDataSet(0, "/data/throttle_left",
                           HOFFSET(SecondaryControls, throttle_left),
                           dueca::get_hdf5_elt_type(example.throttle_left),
                           dueca::get_hdf5_elt_length(example.throttle_left));

    this->configureDataSet(1, "/data/throttle_right",
                           HOFFSET(SecondaryControls, throttle_right),
                           dueca::get_hdf5_elt_type(example.throttle_right),
                           dueca::get_hdf5_elt_length(example.throttle_right));

    this->configureDataSet(2, "/data/flap_setting",
                           HOFFSET(SecondaryControls, flap_setting),
                           dueca::get_hdf5_elt_type(example.flap_setting),
                           dueca::get_hdf5_elt_length(example.flap_setting));

    this->configureDataSet(3, "/data/speedbrake",
                           HOFFSET(SecondaryControls, speedbrake),
                           dueca::get_hdf5_elt_type(example.speedbrake),
                           dueca::get_hdf5_elt_length(example.speedbrake));

    if (readticks) {
      dueca::TimeTickType tex;
      this->configureDataSet(4, "/tick", 0,
                             dueca::get_hdf5_elt_type(tex), 1);
    }
  }

  bool HDF5DCOReadFunctor::operator() (void* dpointer)
  {

    this->sets[0].readObjectPart(dpointer, example.throttle_left);

    this->sets[1].readObjectPart(dpointer, example.throttle_right);

    this->sets[2].readObjectPart(dpointer, example.flap_setting);

    this->sets[3].readObjectPart(dpointer, example.speedbrake);

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
} // end namespace SecondaryControls_space
#endif

