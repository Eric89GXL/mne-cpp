//=============================================================================================================
/**
* @file     sphara.cpp
* @author   Lorenz Esch <lorenz.esch@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>;
* @version  1.0
* @date     Februaray, 2016
*
* @section  LICENSE
*
* Copyright (C) 2014, Lorenz Esch, Christoph Dinh and Matti Hamalainen. All rights reserved.
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
* @brief    Implementation of the Sphara class
*
*/

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "sphara.h"


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace UTILSLIB;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

Sphara::Sphara()
{

}


//*************************************************************************************************************

MatrixXd Sphara::makeSpharaProjector(const MatrixXd& matBaseFct, const VectorXi& vecIndices, int iOperatorDim, int iNBaseFct)
{
    MatrixXd matSpharaOperator = MatrixXd::Identity(iOperatorDim, iOperatorDim);

    //Remove unwanted base functions
    MatrixXd matSpharaGradCut = matBaseFct.block(0,0,matBaseFct.rows(),iNBaseFct);
    MatrixXd matSpharaMultGrad = matSpharaGradCut * matSpharaGradCut.transpose().eval();

    //Create the SPHARA operator
    int rowIndex = 0;
    int colIndex = 0;

    for(int r = 0; r<vecIndices.rows(); r++) {
        for(int c = 0; c<vecIndices.rows(); c++) {
            matSpharaOperator(vecIndices(r),vecIndices(c)) = matSpharaMultGrad(rowIndex,colIndex);
            colIndex++;
        }
        colIndex = 0;
        rowIndex++;
    }

    return matSpharaOperator;
}








