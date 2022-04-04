/* ------------------------------------------------------------------ */
/*      item            : BaseObjectMotion.cxx
        generated by    : matteo (matteo)
        date            : Thu 24 Mar 2022
        category        : body file
        description     : DUECA Communication Object (DCO),
                          automatically generated by dueca-codegen
        codegen version : 110
        language        : C++
*/

#include "BaseObjectMotion.hxx"
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




// Additional custom code
#include "BaseObjectMotionExtra.cxx"

// if any custom implementations have been defined, for packing,
// unpacking, construction or deletion, verify that the
// custom code is compatible with the current generation
#if defined(__CUSTOM_DEFAULT_CONSTRUCTOR) || \
    defined(__CUSTOM_FULL_CONSTRUCTOR) || \
    defined(__CUSTOM_FULLSINGLES_CONSTRUCTOR) || \
    defined(__CUSTOM_COPY_CONSTRUCTOR) || \
    defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) || \
    defined(__CUSTOM_ARRAYS_SIZE_INIT_CONSTRUCTOR) || \
    defined(__CUSTOM_DESTRUCTOR) || \
    defined(__CUSTOM_FUNCTION_PACKDATADIFF) || \
    defined(__CUSTOM_FUNCTION_UNPACKDATA) || \
    defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) || \
    defined(__CUSTOM_FUNCTION_PACKDATA) || \
    defined(__CUSTOM_HDF5_WRITE_FUNCTOR) || \
    defined(__CUSTOM_HDF5_READ_FUNCTOR)
#ifndef __CUSTOM_COMPATLEVEL_110
#error "Verify that your custom code is compatible with version 110. Then define __CUSTOM_COMPATLEVEL_110"
#endif
#endif
#define DUECA_HDF_CODEGEN_VERSION 1
#if defined(__CUSTOM_HDF5_WRITE_FUNCTOR) || \
    defined(__CUSTOM_HDF5_READ_FUNCTOR)
#ifndef __CUSTOM_COMPATLEVEL_HDF_1
#error "Verify custom hdf code compatibility with version 1.\
 Then define __CUSTOM_COMPATLEVEL_HDF_1"
#endif
#endif



#if !defined(__DCO_STANDALONE)
// static CommObjectMemberAccess objects, that can provide flexible access
// to the members of a BaseObjectMotion object
static ::dueca::CommObjectMemberAccess
  <BaseObjectMotion,dueca::fixvector<3,float> >
  BaseObjectMotion_member_omega(&BaseObjectMotion::omega, "omega");
static ::dueca::CommObjectMemberAccess
  <BaseObjectMotion,dueca::fixvector<3,float> >
  BaseObjectMotion_member_uvw(&BaseObjectMotion::uvw, "uvw");
static ::dueca::CommObjectMemberAccess
  <BaseObjectMotion,float >
  BaseObjectMotion_member_dt(&BaseObjectMotion::dt, "dt");

// assemble the above entries into a table in the order in which they
// appear in the BaseObjectMotion object
static const ::dueca::CommObjectDataTable entriestable[] = {
  { &BaseObjectMotion_member_omega },
  { &BaseObjectMotion_member_uvw },
  { &BaseObjectMotion_member_dt },
  { NULL }
};

#endif

// class name, static
const char * const BaseObjectMotion::classname = "BaseObjectMotion";

// magic number, hashed from class name and member names / classes
const uint32_t BaseObjectMotion::magic_check_number=0x4908a6f1;

#if !defined(__DCO_STANDALONE)
// functor table, provides access to user-defined metafunctions through the
// data class registry
static dueca::functortable_type functortable;

// register this class, provides access to a packing/unpacking object,
// and to the member access tables
static ::dueca::DataClassRegistrar registrar
  (BaseObjectMotion::classname, BaseObjectPosition::classname,
   entriestable, &functortable,
   new ::dueca::DataSetSubsidiary<BaseObjectMotion>());

#endif

#ifndef __CUSTOM_DEFAULT_CONSTRUCTOR
BaseObjectMotion::BaseObjectMotion():
    omega(0.0f),
    uvw(0.0f),
    dt(0.0f)
{
  DOBS("default constructor BaseObjectMotion");
}
#endif

#ifndef __CUSTOM_FULL_CONSTRUCTOR
BaseObjectMotion::BaseObjectMotion(
        const BaseObjectPosition& parent_BaseObjectPosition,
        const dueca::fixvector<3,float>& omega,
        const dueca::fixvector<3,float>& uvw,
        const float& dt) :
        BaseObjectPosition(parent_BaseObjectPosition),
    omega(omega),
    uvw(uvw),
    dt(dt)
{
  DOBS("complete constructor BaseObjectMotion");
}
#endif

#ifndef __CUSTOM_FULLSINGLES_CONSTRUCTOR
BaseObjectMotion::BaseObjectMotion(
        const float& dt) :
    dt(dt)
{
  DOBS("complete single argument constructor BaseObjectMotion");
}
#endif

#ifndef __CUSTOM_COPY_CONSTRUCTOR
BaseObjectMotion::BaseObjectMotion(const BaseObjectMotion& other):
        BaseObjectPosition(other),
    omega(other.omega),
    uvw(other.uvw),
    dt(other.dt)
{
  DOBS("copy constructor BaseObjectMotion");
}
#endif

#if !defined(__CUSTOM_AMORPHRESTORE_CONSTRUCTOR) && !defined(__DCO_NOPACK)
BaseObjectMotion::BaseObjectMotion(dueca::AmorphReStore& s):
        BaseObjectPosition(s),
        dt(s)
{
  ::dueca::unpackiterable(s, this->omega,
                          dueca::pack_traits<dueca::fixvector<3,float> >()); 
  ::dueca::unpackiterable(s, this->uvw,
                          dueca::pack_traits<dueca::fixvector<3,float> >()); 
  DOBS("amorph constructor BaseObjectMotion");
}
#endif

#if !defined(__CUSTOM_ARRAY_SIZE_INIT_CONSTRUCTOR)
#endif

#ifndef __CUSTOM_DESTRUCTOR
BaseObjectMotion::~BaseObjectMotion()
{
  DOBS("destructor BaseObjectMotion");
}
#endif

#if !defined(__DCO_STANDALONE)
void* BaseObjectMotion::operator new(size_t size)
{
  DOBS("operator new BaseObjectMotion");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(BaseObjectMotion));
  return my_arena->alloc(size);
}

void BaseObjectMotion::operator delete(void* v)
{
  DOBS("operator delete BaseObjectMotion");
  static ::dueca::Arena* my_arena = arena_pool.findArena
    (sizeof(BaseObjectMotion));
  my_arena->free(v);
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATADIFF) && !defined(__DCO_NOPACK)
void BaseObjectMotion::packDataDiff(::dueca::AmorphStore& s, const BaseObjectMotion& ref) const
{
  DOBS("packDataDiff BaseObjectMotion");
  ::dueca::IndexMemory im;
        this->BaseObjectPosition::packDataDiff(s, ref);
  ::dueca::checkandpackdiffiterable(this->omega, ref.omega, s, im,
                          dueca::diffpack_traits<dueca::fixvector<3,float> >());
  ::dueca::checkandpackdiffiterable(this->uvw, ref.uvw, s, im,
                          dueca::diffpack_traits<dueca::fixvector<3,float> >());
  ::dueca::checkandpackdiffsingle(this->dt, ref.dt,
                         s, im);
  im.closeoff(s);
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATA) && !defined(__DCO_NOPACK)
void BaseObjectMotion::unPackData(::dueca::AmorphReStore& s)
{
  DOBS("unPackData BaseObjectMotion");

        this->BaseObjectPosition::unPackData(s);
  ::unPackData(s, this->dt);

  ::dueca::unpackiterable(s, this->omega,
                          dueca::pack_traits<dueca::fixvector<3,float> >()); 
  ::dueca::unpackiterable(s, this->uvw,
                          dueca::pack_traits<dueca::fixvector<3,float> >()); 
}
#endif

#if !defined(__CUSTOM_FUNCTION_UNPACKDATADIFF) && !defined(__DCO_NOPACK)
void BaseObjectMotion::unPackDataDiff(dueca::AmorphReStore& s)
{
  DOBS("unPackDataDiff BaseObjectMotion");
  ::dueca::IndexRecall im;
        this->BaseObjectPosition::unPackDataDiff(s);
  ::dueca::checkandunpackdiffiterable(this->omega, s, im,
                          dueca::diffpack_traits<dueca::fixvector<3,float> >());
  ::dueca::checkandunpackdiffiterable(this->uvw, s, im,
                          dueca::diffpack_traits<dueca::fixvector<3,float> >());
  ::dueca::checkandunpackdiffsingle(this->dt, s, im);
}
#endif

#ifndef __CUSTOM_OPERATOR_EQUAL
bool BaseObjectMotion::operator == (const BaseObjectMotion& other) const
{
  DOBS("operator == BaseObjectMotion");
  if (this->BaseObjectPosition::operator != (other)) return false;
  if (this->omega != other.omega) return false;
  if (this->uvw != other.uvw) return false;
  if (this->dt != other.dt) return false;
  return true;
}
#endif

#ifndef __CUSTOM_OPERATOR_ASSIGN
BaseObjectMotion&
BaseObjectMotion::operator=(const BaseObjectMotion& other)
{
  DOBS("operator = BaseObjectMotion");
  if (this == &other) return *this;
        this->BaseObjectPosition::operator=(other);
  this->omega = other.omega;
  this->uvw = other.uvw;
  this->dt = other.dt;
  return *this;
}
#endif

#if !defined(__CUSTOM_FUNCTION_PACKDATA) && !defined(__DCO_NOPACK)
void BaseObjectMotion::packData(::dueca::AmorphStore& s) const
{
  DOBS("packData BaseObjectMotion");
        this->BaseObjectPosition::packData(s);
  ::packData(s, this->dt);
  ::dueca::packiterable(s, this->omega,
                        dueca::pack_traits<dueca::fixvector<3,float> >()); 
  ::dueca::packiterable(s, this->uvw,
                        dueca::pack_traits<dueca::fixvector<3,float> >()); 
}
#endif

#ifndef __CUSTOM_FUNCTION_PRINT
std::ostream & BaseObjectMotion::print(std::ostream& s) const
{
  s << "BaseObjectMotion(";
  this->BaseObjectPosition::print(s);
  s
    << "omega={";
  for (dueca::fixvector<3,float>::const_iterator ii = this->omega.begin();
       ii != this->omega.end(); ii++) {
    if (ii != this->omega.begin()) s << ',';
    s << (*ii);
  }
  s << "},"
    << "uvw={";
  for (dueca::fixvector<3,float>::const_iterator ii = this->uvw.begin();
       ii != this->uvw.end(); ii++) {
    if (ii != this->uvw.begin()) s << ',';
    s << (*ii);
  }
  s << "},"
    << "dt=" << this->dt
    << ')';
  return s;
}
#endif


#if defined(DUECA_CONFIG_HDF5)
// guarded in a separate namespace
namespace BaseObjectMotion_space {

#if !defined(__CUSTOM_HDF5_WRITE_FUNCTOR)
  HDF5DCOWriteFunctor::
  HDF5DCOWriteFunctor(boost::weak_ptr<H5::H5File> file,
                      const std::string& path,
                      size_t chunksize,
                      const std::string& label,
                      bool compress, bool writeticks,
                      const dueca::DataTimeSpec* startend) :
    dueca::hdf5log::HDF5DCOWriteFunctor(file, path, chunksize, label,
                               3, compress, writeticks,
                               startend),
    __parent__(file, path + std::string("/__parent__"), chunksize,
               std::string(""), compress, false, startend)
  {
    // add memspaces for all elements

    this->configureDataSet(0, "/data/omega",
                           HOFFSET(BaseObjectMotion, omega),
                           dueca::get_hdf5_elt_type(example.omega),
                           dueca::get_hdf5_elt_length(example.omega));

    this->configureDataSet(1, "/data/uvw",
                           HOFFSET(BaseObjectMotion, uvw),
                           dueca::get_hdf5_elt_type(example.uvw),
                           dueca::get_hdf5_elt_length(example.uvw));

    this->configureDataSet(2, "/data/dt",
                           HOFFSET(BaseObjectMotion, dt),
                           dueca::get_hdf5_elt_type(example.dt),
                           dueca::get_hdf5_elt_length(example.dt));

    if (writeticks) {
      dueca::TimeTickType tex;
      this->configureDataSet(3, "/tick", 0,
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

    this->sets[0].writeNew(dpointer, chunkidx, example.omega);

    this->sets[1].writeNew(dpointer, chunkidx, example.uvw);

    this->sets[2].writeNew(dpointer, chunkidx, example.dt);

    if (writeticks) {
      this->sets[3].writeNew(&ts);
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
                              3, readticks),
    __parent__(file, path + std::string("__parent__"), false)
  {
    // add memspaces for all elements

    this->configureDataSet(0, "/data/omega",
                           HOFFSET(BaseObjectMotion, omega),
                           dueca::get_hdf5_elt_type(example.omega),
                           dueca::get_hdf5_elt_length(example.omega));

    this->configureDataSet(1, "/data/uvw",
                           HOFFSET(BaseObjectMotion, uvw),
                           dueca::get_hdf5_elt_type(example.uvw),
                           dueca::get_hdf5_elt_length(example.uvw));

    this->configureDataSet(2, "/data/dt",
                           HOFFSET(BaseObjectMotion, dt),
                           dueca::get_hdf5_elt_type(example.dt),
                           dueca::get_hdf5_elt_length(example.dt));

    if (readticks) {
      dueca::TimeTickType tex;
      this->configureDataSet(3, "/tick", 0,
                             dueca::get_hdf5_elt_type(tex), 1);
    }
  }

  bool HDF5DCOReadFunctor::operator() (void* dpointer)
  {

    __parent__.operator() (dpointer);
    this->sets[0].readObjectPart(dpointer, example.omega);

    this->sets[1].readObjectPart(dpointer, example.uvw);

    this->sets[2].readObjectPart(dpointer, example.dt);

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
} // end namespace BaseObjectMotion_space
#endif
