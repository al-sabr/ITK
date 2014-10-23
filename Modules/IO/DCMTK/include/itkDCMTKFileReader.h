/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkDCMTKFileReader_h

#define __itkDCMTKFileReader_h
#include "ITKIODCMTKExport.h"
#include <stack>
#include <vector>
#include "itkByteSwapper.h"
#include "itkIntTypes.h"
#include "vnl/vnl_vector.h"
#include "dcdict.h"             // For DcmDataDictionary
#include "dcdicent.h"
#include "dcxfer.h"
#include "dcvrds.h"
#include "dcstack.h"
#include "dcdatset.h"
#include "dcitem.h"
#include "dcvrobow.h"
#include "dcsequen.h"
#include "itkMacro.h"
#include "itkImageIOBase.h"

class DcmSequenceOfItems;
class DcmFileFormat;
class DcmDictEntry;

// Don't print error messages if you're not throwing
// an exception
//     std::cerr body;
#define DCMTKExceptionOrErrorReturn(body)       \
  {                                             \
    if(throwException)                          \
      {                                         \
      itkGenericExceptionMacro(body);           \
      }                                         \
    else                                        \
      {                                         \
      return EXIT_FAILURE;                      \
      }                                         \
  }

namespace itk
{
class ITKIODCMTK_EXPORT DCMTKSequence;

class ITKIODCMTK_EXPORT DCMTKItem
{
public:
  DCMTKItem() : m_DcmItem(0)
    {
    }
  void SetDcmItem(DcmItem *item);
  int GetElementSQ(unsigned short group,
                   unsigned short entry,
                   DCMTKSequence &sequence,
                   bool throwException = true);

private:
  DcmItem *m_DcmItem;
};

class ITKIODCMTK_EXPORT DCMTKSequence
{
public:
  DCMTKSequence() : m_DcmSequenceOfItems(0) {}
  void SetDcmSequenceOfItems(DcmSequenceOfItems *seq);
  int card();
  int GetSequence(unsigned long index,
                  DCMTKSequence &target,bool throwException = true);
  int GetStack(unsigned short group,
               unsigned short element,
               DcmStack &resultStack, bool throwException = true);
  int GetElementCS(unsigned short group,
                   unsigned short element,
                   std::string &target,
                   bool throwException = true);

  int GetElementOB(unsigned short group,
                   unsigned short element,
                   std::string &target,
                   bool throwException = true);

  int GetElementCSorOB(unsigned short group,
                       unsigned short element,
                       std::string &target,
                       bool throwException = true);

  template <typename TType>
  int  GetElementDSorOB(unsigned short group,
                        unsigned short element,
                        TType  &target,
                        bool throwException = true)
    {
      if(this->GetElementDS<TType>(group,element,1,&target,false) == EXIT_SUCCESS)
        {
        return EXIT_SUCCESS;
        }
      std::string val;
      if(this->GetElementOB(group,element,val,throwException) != EXIT_SUCCESS)
        {
        DCMTKExceptionOrErrorReturn(<< "Cant find DecimalString element " << std::hex
                       << group << " " << std::hex
                       << element << std::dec);
        }
      const char *data = val.c_str();
      const TType *fptr = reinterpret_cast<const TType *>(data);
      target = *fptr;
      return EXIT_SUCCESS;

    }

  template <typename TType>
  int  GetElementDSorOB(unsigned short group,
                        unsigned short element,
                        int count,
                        TType  *target,
                        bool throwException = true)
    {
      if(this->GetElementDS<TType>(group,element,count,target,false) == EXIT_SUCCESS)
        {
        return EXIT_SUCCESS;
        }
      std::string val;
      if(this->GetElementOB(group,element,val,throwException) != EXIT_SUCCESS)
        {
        DCMTKExceptionOrErrorReturn(<< "Cant find DecimalString element " << std::hex
                       << group << " " << std::hex
                       << element << std::dec);
        }
      const char *data = val.c_str();
      const TType *fptr = reinterpret_cast<const TType *>(data);
      for(int i = 0; i < count; ++i)
        {
        target[i] = fptr[i];
        }
      return EXIT_SUCCESS;
    }


  int GetElementFD(unsigned short group,
                   unsigned short element,
                   int count,
                   double *target,
                   bool throwException = true);
  int GetElementFD(unsigned short group,
                   unsigned short element,
                   double &target,
                   bool throwException = true);
  int GetElementDS(unsigned short group,
                   unsigned short element,
                   std::string &target,
                   bool throwException = true);
  int GetElementTM(unsigned short group,
                   unsigned short element,
                   std::string &target,
                   bool throwException = true);
  /** Get an array of data values, as contained in a DICOM
    * DecimalString Item
    */
  template <typename TType>
  int GetElementDS(unsigned short group,
                   unsigned short element,
                   unsigned short count,
                   TType  *target,
                   bool throwException = true)
    {
      DcmStack resultStack;
      if(this->GetStack(group,element,resultStack,throwException) != EXIT_SUCCESS)
        {
        return EXIT_FAILURE;
        }
      DcmDecimalString *dsItem =
        dynamic_cast<DcmDecimalString *>(resultStack.top());
      if(dsItem == 0)
        {
        DCMTKExceptionOrErrorReturn(<< "Can't get DecimalString Element at tag "
                       << std::hex << group << " "
                       << element << std::dec);
        }

      OFVector<Float64> doubleVals;
      if(dsItem->getFloat64Vector(doubleVals) != EC_Normal)
        {
        DCMTKExceptionOrErrorReturn(<< "Cant extract Array from DecimalString " << std::hex
                       << group << " " << std::hex
                       << element << std::dec);
        }
      if(doubleVals.size() != count)
        {
        DCMTKExceptionOrErrorReturn(<< "DecimalString " << std::hex
                       << group << " " << std::hex
                       << element << " expected "
                       << count << "items, but found "
                       << doubleVals.size() << std::dec);

        }
      for(unsigned i = 0; i < count; i++)
        {
        target[i] = static_cast<TType>(doubleVals[i]);
        }
      return EXIT_SUCCESS;
    }
  int GetElementSQ(unsigned short group,
                   unsigned short element,
                   DCMTKSequence &target,
                   bool throwException = true);
  int GetElementItem(unsigned short itemIndex,
                     DCMTKItem &target,
                     bool throwException = true);

  void print(std::ostream &out)
    {
      this->m_DcmSequenceOfItems->print(out);
    }
private:
  DcmSequenceOfItems *m_DcmSequenceOfItems;
};

class ITKIODCMTK_EXPORT DCMTKFileReader
{
public:
  typedef DCMTKFileReader Self;

  DCMTKFileReader() : m_DFile(0),
                      m_Dataset(0),
                      m_Xfer(EXS_Unknown),
                      m_FrameCount(0),
                      m_FileNumber(-1L),
                      m_Origin(0);
    {
    }
  ~DCMTKFileReader();

  void SetFileName(const std::string &fileName);

  const std::string &GetFileName() const;

  void LoadFile();

  int GetElementLO(unsigned short group,
                   unsigned short element,
                   std::string &target,
                   bool throwException = true);
  int GetElementLO(unsigned short group,
                   unsigned short element,
                   std::vector<std::string> &target,
                   bool throwException = true);

  /** Get an array of data values, as contained in a DICOM
    * DecimalString Item
    */
  template <typename TType>
  int  GetElementDS(unsigned short group,
                    unsigned short element,
                    unsigned short count,
                    TType  *target,
                    bool throwException = true)
    {
      DcmTagKey tagkey(group,element);
      DcmElement *el;
      if(this->m_Dataset->findAndGetElement(tagkey,el) != EC_Normal)
        {
        DCMTKExceptionOrErrorReturn(<< "Cant find tag " << std::hex
                       << group << " " << std::hex
                       << element << std::dec);
        }
      DcmDecimalString *dsItem = dynamic_cast<DcmDecimalString *>(el);
      if(dsItem == 0)
        {
        DCMTKExceptionOrErrorReturn(<< "Cant find DecimalString element " << std::hex
                       << group << " " << std::hex
                       << element << std::dec);
        }
      OFVector<Float64> doubleVals;
      if(dsItem->getFloat64Vector(doubleVals) != EC_Normal)
        {
        DCMTKExceptionOrErrorReturn(<< "Cant extract Array from DecimalString " << std::hex
                       << group << " " << std::hex
                       << element << std::dec);
        }
      if(doubleVals.size() != count)
        {
        DCMTKExceptionOrErrorReturn(<< "DecimalString " << std::hex
                       << group << " " << std::hex
                       << element << " expected "
                       << count << "items, but found "
                       << doubleVals.size() << std::dec);

        }
      for(unsigned i = 0; i < count; i++)
        {
        target[i] = static_cast<TType>(doubleVals[i]);
        }
      return EXIT_SUCCESS;
    }

  template <typename TType>
  int  GetElementDSorOB(unsigned short group,
                        unsigned short element,
                        TType  &target,
                        bool throwException = true)
    {
      if(this->GetElementDS<TType>(group,element,1,&target,false) == EXIT_SUCCESS)
        {
        return EXIT_SUCCESS;
        }
      std::string val;
      if(this->GetElementOB(group,element,val) != EXIT_SUCCESS)
        {
        DCMTKExceptionOrErrorReturn(<< "Cant find DecimalString element " << std::hex
                       << group << " " << std::hex
                       << element << std::dec);
        }
      const char *data = val.c_str();
      const TType *fptr = reinterpret_cast<const TType *>(data);
      target = *fptr;
      switch(this->GetTransferSyntax())
        {
        case EXS_LittleEndianImplicit:
        case EXS_LittleEndianExplicit:
          itk::ByteSwapper<TType>::SwapFromSystemToLittleEndian(&target);
          break;
        case EXS_BigEndianImplicit:
        case EXS_BigEndianExplicit:
          itk::ByteSwapper<TType>::SwapFromSystemToBigEndian(&target);
          break;
        default:
          break;
        }
      return EXIT_SUCCESS;

    }
  /** Get a DecimalString Item as a single string
   */
  int  GetElementDS(unsigned short group,
                    unsigned short element,
                    std::string &target,
                    bool throwException = true);
  int  GetElementFD(unsigned short group,
                    unsigned short element,
                    double &target,
                    bool throwException = true);
  int  GetElementFD(unsigned short group,
                    unsigned short element,
                    int count,
                    double * target,
                    bool throwException = true);
  int  GetElementFL(unsigned short group,
                    unsigned short element,
                    float &target,
                    bool throwException = true);
  int  GetElementFLorOB(unsigned short group,
                        unsigned short element,
                        float &target,
                        bool throwException = true);

  int  GetElementUS(unsigned short group,
                    unsigned short element,
                    unsigned short &target,
                    bool throwException = true);
  int  GetElementUS(unsigned short group,
                    unsigned short element,
                    unsigned short *&target,
                    bool throwException = true);
  /** Get a DecimalString Item as a single string
   */
  int  GetElementCS(unsigned short group,
                    unsigned short element,
                    std::string &target,
                    bool throwException = true);

  /** Get a PersonName Item as a single string
   */
  int  GetElementPN(unsigned short group,
                    unsigned short element,
                    std::string &target,
                    bool throwException = true);

  /** get an IS (Integer String Item
   */
  int  GetElementIS(unsigned short group,
                    unsigned short element,
                    ::itk::int32_t  &target,
                    bool throwException = true);

  int  GetElementSL(unsigned short group,
                    unsigned short element,
                    ::itk::int32_t  &target,
                    bool throwException = true);

  int  GetElementISorOB(unsigned short group,
                        unsigned short element,
                        ::itk::int32_t  &target,
                        bool throwException = true);

  int  GetElementCSorOB(unsigned short group,
                        unsigned short element,
                        std::string &target,
                        bool throwException = true);

  /** get an OB OtherByte Item
   */
  int  GetElementOB(unsigned short group,
                    unsigned short element,
                    std::string &target,
                    bool throwException = true);

  int GetElementSQ(unsigned short group,
                   unsigned short entry,
                   DCMTKSequence &sequence,
                   bool throwException = true);

  int GetElementUI(unsigned short group,
                  unsigned short entry,
                  std::string &target,
                   bool throwException = true);

  int GetElementDA(unsigned short group,
                   unsigned short element,
                   std::string &target,
                   bool throwException = true);

  int GetElementTM(unsigned short group,
                   unsigned short element,
                   std::string &target,
                   bool throwException = true);

  int GetDirCosines(vnl_vector<double> &dir1,
                    vnl_vector<double> &dir2,
                    vnl_vector<double> &dir3);

  int GetDirCosArray(double *dircos);

  int GetFrameCount() const;

  int GetSlopeIntercept(double &slope, double &intercept);

  int GetDimensions(unsigned short &rows, unsigned short &columns);

  ImageIOBase::IOComponentType GetImageDataType();
  ImageIOBase::IOPixelType GetImagePixelType();

  int GetSpacing(double *spacing);
  int GetOrigin(double *origin);

  bool HasPixelData() const;

  E_TransferSyntax GetTransferSyntax() const;

  long GetFileNumber() const;
  static void
  AddDictEntry(DcmDictEntry *entry);

  static bool CanReadFile(const std::string &filename);
  static bool IsImageFile(const std::string &filename);

private:

  std::string          m_FileName;
  DcmFileFormat*       m_DFile;
  DcmDataset *         m_Dataset;
  E_TransferSyntax     m_Xfer;
  Sint32               m_FrameCount;
  long                 m_FileNumber;
  double *             m_Origin;
};

extern bool CompareDCMTKFileReaders(DCMTKFileReader *a, DCMTKFileReader *b);
}

#endif // __itkDCMTKFileReader_h
