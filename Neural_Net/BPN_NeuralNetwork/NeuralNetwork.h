//-------------------------------------------------------------------------
// Simple back-propagation neural network example
// 2017 - Bobby Anguelov
// MIT license: https://opensource.org/licenses/MIT
//-------------------------------------------------------------------------

/*
 * main.cpp
 *
 *  Created on: 8 wrz 2018
 *      Author: damian
 */


#pragma once
#include <stdint.h>
#include <vector>
#include <cmath>
#include <string>

namespace BPN
{
     enum class ActivationFunctionType{Sigmoid};

    class Network
    {
        friend class NetworkTrainer;

        inline static double SigmoidActivationFunction( double x )
        {
            return 1.0 / ( 1.0 + std::exp( -x ) );
        }

        inline static int32_t ClampOutputValue( double x )
        {
            if ( x < 0.1 ) return 0;
            else if ( x > 0.9 ) return 1;
            else return -1;
        }

    public:
        struct Settings
        {
            uint32_t                        m_numInputs;
            uint32_t                        m_numHidden;
            uint32_t                        m_numOutputs;
            std::string 					weights_file_name;
            std::string						neurons_file_name;
        };

    public:
        Network( Settings const& settings,unsigned int set, std::vector<double> const &buffer = std::vector<double>(0));
        std::vector<int32_t> const& Evaluate( std::vector<double> const& input );

        void SaveWeightsIntoFile() const;
        void SaveWeightsIntoBuffer(std::vector<double> *weights);
        void SaveNeuronsIntoFile() const;
        void LoadWeightsFromFile();
        void LoadWeightsFromBuffer(std::vector<double> const &weights);

    private:
        void InitializeNetwork();
        void InitializeWeights();

        int32_t GetInputHiddenWeightIndex( int32_t inputIdx, int32_t hiddenIdx ) const { return inputIdx * m_numHidden + hiddenIdx; }
        int32_t GetHiddenOutputWeightIndex( int32_t hiddenIdx, int32_t outputIdx ) const { return hiddenIdx * m_numOutputs + outputIdx; }

    public:
        std::vector<double>     m_inputNeurons;
        std::vector<double>     m_hiddenNeurons;
        std::vector<double>     m_outputNeurons;

    private:
        int32_t                 m_numInputs;
        int32_t                 m_numHidden;
        int32_t                 m_numOutputs;

        std::vector<int32_t>    m_clampedOutputs;

        std::vector<double>     m_weightsInputHidden;
        std::vector<double>     m_weightsHiddenOutput;

        std::string 			weights_file_name;
        std::string 			neurons_file_name;
    };
}
