//=============================================================================================================
/**
* @file     mne_raw_data.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     January, 2017
*
* @section  LICENSE
*
* Copyright (C) 2017, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    MneRawData class declaration.
*
*/

#ifndef MNERAWDATA_H
#define MNERAWDATA_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../inverse_global.h"

#include <fiff/fiff_dir_node.h>
#include <fiff/fiff_stream.h>
#include "mne_raw_info.h"
#include "mne_raw_buf_def.h"
#include "mne_proj_op.h"
#include "mne_sss_data.h"
#include "mne_ctf_comp_data_set.h"
#include "mne_types.h"



//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================

#include <Eigen/Core>


//*************************************************************************************************************
//=============================================================================================================
// Qt INCLUDES
//=============================================================================================================

#include <QSharedPointer>
#include <QList>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE INVERSELIB
//=============================================================================================================

namespace INVERSELIB
{

//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================


//=============================================================================================================
/**
* Implements the MNE Raw Data (Replaces *mneRawData,mneRawDataRec; struct of MNE-C mne_types.h).
*
* @brief A comprehensive raw data structure
*/
class INVERSESHARED_EXPORT MneRawData
{
public:
    typedef QSharedPointer<MneRawData> SPtr;              /**< Shared pointer type for MneRawData. */
    typedef QSharedPointer<const MneRawData> ConstSPtr;   /**< Const shared pointer type for MneRawData. */

    //=========================================================================================================
    /**
    * Constructs the MNE Raw Data
    * Refactored: new_raw_data (mne_raw_data.c)
    */
    MneRawData();

    //=========================================================================================================
    /**
    * Destroys the MNE Raw Data
    * Refactored: mne_raw_free_data (mne_raw_data.c)
    */
    ~MneRawData();

public:
    char             *filename;             /* This is our file */
    //  FIFFLIB::fiffFile       file;
    FIFFLIB::FiffStream::SPtr stream;
    INVERSELIB::MneRawInfo*      info;      /* Loaded using the mne routines */
    char             **ch_names;            /* Useful to have the channel names as a single list */
    char             **badlist;             /* Bad channel names */
    int              nbad;                  /* How many? */
    int              *bad;                  /* Which channels are bad? */
    INVERSELIB::MneRawBufDef* bufs;         /* These are the data */
    int              nbuf;                  /* How many? */
    INVERSELIB::MneRawBufDef* filt_bufs;    /* These are the filtered ones */
    int              nfilt_buf;
    int              first_samp;            /* First sample? */
    int              omit_samp;             /* How many samples of skip omitted in the beginning */
    int              first_samp_old;        /* This is the value first_samp would have in the old versions */
    int              omit_samp_old;         /* This is the value omit_samp would have in the old versions */
    int              nsamp;                 /* How many samples in total? */
    float            *first_sample_val;     /* Values at the first sample (for dc offset correction before filtering) */
    INVERSELIB::MneProjOp* proj;            /* Projection operator */
    INVERSELIB::MneSssData* sss;            /* SSS data found in this file */
    INVERSELIB::MneCTFCompDataSet* comp;    /* Compensation data */
    int              comp_file;             /* Compensation status of these raw data in file */
    int              comp_now;              /* Compensation status of these raw data in file */
    mneFilterDef     filter;                /* Filter definition */
    void             *filter_data;          /* This can be whatever the filter needs */
    mneUserFreeFunc  filter_data_free;      /* Function to free the above */
    mneEventList     event_list;            /* Trigger events */
    unsigned int     max_event;             /* Maximum event number in usenest */
    char             *dig_trigger;          /* Name of the digital trigger channel */
    unsigned int     dig_trigger_mask;      /* Mask applied to digital trigger channel before considering it */
    float            *offsets;              /* Dc offset corrections for display */
    void             *ring;                 /* The ringbuffer (structure is of no interest to us) */
    void             *filt_ring;            /* Separate ring buffer for filtered data */
    INVERSELIB::MneDerivSet*  deriv;        /* Derivation data */
    INVERSELIB::MneDeriv*     deriv_matched;/* Derivation data matched to this raw data and collected into a single item */
    float            *deriv_offsets;        /* Dc offset corrections for display of the derived channels */
    void             *user;         /* Whatever */
    mneUserFreeFunc  user_free;     /* How this is freed */

//// ### OLD STRUCT ###
//typedef struct {        /* A comprehensive raw data structure */
//    char             *filename;             /* This is our file */
//    //  FIFFLIB::fiffFile       file;
//    FIFFLIB::FiffStream::SPtr stream;
//    INVERSELIB::MneRawInfo*      info;      /* Loaded using the mne routines */
//    char             **ch_names;            /* Useful to have the channel names as a single list */
//    char             **badlist;             /* Bad channel names */
//    int              nbad;                  /* How many? */
//    int              *bad;                  /* Which channels are bad? */
//    INVERSELIB::MneRawBufDef* bufs;         /* These are the data */
//    int              nbuf;                  /* How many? */
//    INVERSELIB::MneRawBufDef* filt_bufs;    /* These are the filtered ones */
//    int              nfilt_buf;
//    int              first_samp;            /* First sample? */
//    int              omit_samp;             /* How many samples of skip omitted in the beginning */
//    int              first_samp_old;        /* This is the value first_samp would have in the old versions */
//    int              omit_samp_old;         /* This is the value omit_samp would have in the old versions */
//    int              nsamp;                 /* How many samples in total? */
//    float            *first_sample_val;     /* Values at the first sample (for dc offset correction before filtering) */
//    INVERSELIB::MneProjOp* proj;            /* Projection operator */
//    INVERSELIB::MneSssData* sss;            /* SSS data found in this file */
//    INVERSELIB::MneCTFCompDataSet* comp;    /* Compensation data */
//    int              comp_file;             /* Compensation status of these raw data in file */
//    int              comp_now;              /* Compensation status of these raw data in file */
//    mneFilterDef     filter;                /* Filter definition */
//    void             *filter_data;          /* This can be whatever the filter needs */
//    mneUserFreeFunc  filter_data_free;      /* Function to free the above */
//    mneEventList     event_list;            /* Trigger events */
//    unsigned int     max_event;             /* Maximum event number in usenest */
//    char             *dig_trigger;          /* Name of the digital trigger channel */
//    unsigned int     dig_trigger_mask;      /* Mask applied to digital trigger channel before considering it */
//    float            *offsets;              /* Dc offset corrections for display */
//    void             *ring;                 /* The ringbuffer (structure is of no interest to us) */
//    void             *filt_ring;            /* Separate ring buffer for filtered data */
//    INVERSELIB::MneDerivSet*  deriv;        /* Derivation data */
//    INVERSELIB::MneDeriv*     deriv_matched;/* Derivation data matched to this raw data and collected into a single item */
//    float            *deriv_offsets;        /* Dc offset corrections for display of the derived channels */
//    void             *user;	        /* Whatever */
//    mneUserFreeFunc  user_free;     /* How this is freed */
//} *mneRawData,mneRawDataRec;
};

//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================

} // NAMESPACE INVERSELIB

#endif // MNERAWDATA_H
