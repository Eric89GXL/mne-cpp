//=============================================================================================================
/**
* @file     tmsiproducer.h
* @author   Lorenz Esch <lorenz.esch@tu-ilmenau.de>;
*           Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     February, 2013
*
* @section  LICENSE
*
* Copyright (C) 2013, Lorenz Esch, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains the declaration of the TMSIProducer class.
*
*/

#ifndef TMSIPRODUCER_H
#define TMSIPRODUCER_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include <generics/circularbuffer.h>


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QThread>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE TMSIPlugin
//=============================================================================================================

namespace TMSIPlugin
{


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace IOBuffer;


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

class TMSI;
class TMSIDriver;


//=============================================================================================================
/**
* DECLARE CLASS EEGProducer
*
* @brief The EEGProducer class provides a EEG data producer for a given sampling rate.
*/
class TMSIProducer : public QThread
{
public:
    //=========================================================================================================
    /**
    * Constructs a TMSIProducer.
    *
    * @param [in] pTMSI a pointer to the corresponding TMSI class.
    */
    TMSIProducer(TMSI* pTMSI);

    //=========================================================================================================
    /**
    * Destroys the TMSIProducer.
    */
    ~TMSIProducer();

    //=========================================================================================================
    /**
    * Starts the TMSIProducer by starting the producer's thread and initialising the device.
    * @param [in] iNumberOfChannels The number of channels defined by the user via the GUI.
    * @param [in] iSamplingFrequency The sampling frequency defined by the user via the GUI (in Hertz).
    * @param [in] iSamplesPerBlock The samples per block defined by the user via the GUI.
    * @param [in] bConvertToVolt Flag for converting the values to Volt. Defined by the user via the GUI.
    * @param [in] bUseChExponent Flag for using the channels exponent. Defined by the user via the GUI.
    * @param [in] bUseUnitGain Flag for using the channels unit gain. Defined by the user via the GUI.
    * @param [in] sOutpuFilePath Holds the path for the output file. Defined by the user via the GUI.
    * @param [in] bWriteToFile Flag for writing the received samples to a file. Defined by the user via the GUI.
    * @param [in] bUsePreProcessing Flag for writing the received samples to a file. Defined by the user via the GUI.
    * @param [in] bUseUnitOffset Flag for using the channels unit offset. Defined by the user via the GUI.
    */
    virtual void start(int iNumberOfChannels,
                       int iSamplingFrequency,
                       int iSamplesPerBlock,
                       bool bConvertToVolt,
                       bool bUseChExponent,
                       bool bUseUnitGain,
                       bool bUseUnitOffset,
                       bool bWriteToFile,
                       bool bUsePreProcessing,
                       QString sOutputFilePath);

    //=========================================================================================================
    /**
    * Stops the TMSIProducer by stopping the producer's thread.
    */
    void stop();

protected:
    //=========================================================================================================
    /**
    * The starting point for the thread. After calling start(), the newly created thread calls this function.
    * Returning from this method will end the execution of the thread.
    * Pure virtual method inherited by QThread.
    */
    virtual void run();

private:
    TMSI*                       m_pTMSI;            /**< A pointer to the corresponding TMSI class.*/
    QSharedPointer<TMSIDriver>  m_pTMSIDriver;      /**< A pointer to the corresponding TMSI driver class.*/

    bool                        m_bIsRunning;       /**< Whether TMSIProducer is running.*/

};

} // NAMESPACE

#endif // TMSIPRODUCER_H