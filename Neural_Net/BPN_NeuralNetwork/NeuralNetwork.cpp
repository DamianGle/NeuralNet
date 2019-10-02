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

#include "../BPN_NeuralNetwork/NeuralNetwork.h"

#include <assert.h>
#include <stdlib.h>
#include <ctime>
#include <random>
#include <cstring>
#include <fstream>
#include <iostream>
namespace BPN
{
    Network::Network( Settings const& settings, unsigned int set, std::vector<double> const & buffer )
        : m_numInputs( settings.m_numInputs )
        , m_numHidden( settings.m_numHidden )
        , m_numOutputs( settings.m_numOutputs )
    	, weights_file_name( settings.weights_file_name )
    	, neurons_file_name( settings.neurons_file_name )
    {
        assert( settings.m_numInputs > 0 && settings.m_numOutputs > 0 && settings.m_numHidden > 0 );
        InitializeNetwork();
        if(set == 0) InitializeWeights();
        if(set == 1) LoadWeightsFromFile();
        if(set == 2) LoadWeightsFromBuffer(buffer);
    }

    void Network::SaveWeightsIntoFile() const
    {
        std::fstream file;
        file.open( weights_file_name, std::ios::in | std::ios::trunc | std::ios::out );

        if(file.good() == true)
        	{
        		int32_t  numInputHiddenWeights = m_numInputs * m_numHidden;
        		int32_t  numHiddenOutputWeights = m_numHidden * m_numOutputs;

        		for ( auto InputHiddenIdx = 0; InputHiddenIdx < numInputHiddenWeights; InputHiddenIdx++ )
        			file << m_weightsInputHidden[InputHiddenIdx] << std::endl;

        	    for ( auto HiddenOutputIdx = 0; HiddenOutputIdx < numHiddenOutputWeights; HiddenOutputIdx++ )
        	        file << m_weightsHiddenOutput[HiddenOutputIdx] << std::endl;
        	}
        file.close();
    }

    void Network::SaveWeightsIntoBuffer(std::vector<double> *weights)
    {
		int32_t  numInputHiddenWeights = m_numInputs * m_numHidden;
		int32_t  numHiddenOutputWeights = m_numHidden * m_numOutputs;

		for ( auto InputHiddenIdx = 0; InputHiddenIdx < numInputHiddenWeights; InputHiddenIdx++ )
				weights->push_back(m_weightsInputHidden[InputHiddenIdx]);
	    for ( auto HiddenOutputIdx = 0; HiddenOutputIdx < numHiddenOutputWeights; HiddenOutputIdx++ )
	    		weights->push_back(m_weightsHiddenOutput[HiddenOutputIdx]);
    }

    void Network::LoadWeightsFromFile()
    {
    	std::vector<double> weights;

        std::fstream file;
        double value;

        file.open( weights_file_name, std::ios::in | std::ios::out );

        if(file.good() == true)
        	{
        		file >> value;
        		while(!file.eof())
        			{
        				weights.push_back(value);
        				file >> value;
        			}
        		file.close();

        		int32_t  numInputHiddenWeights = m_numInputs * m_numHidden;
        	    int32_t  numHiddenOutputWeights = m_numHidden * m_numOutputs;
        	    assert( weights.size() == (unsigned int)(numInputHiddenWeights + numHiddenOutputWeights));

        	    int32_t weightIdx = 0;
        	    for ( auto InputHiddenIdx = 0; InputHiddenIdx < numInputHiddenWeights; InputHiddenIdx++ )
        	        {
        	            m_weightsInputHidden[InputHiddenIdx] = weights[weightIdx];
        	            weightIdx++;
        	        }

        	    for ( auto HiddenOutputIdx = 0; HiddenOutputIdx < numHiddenOutputWeights; HiddenOutputIdx++ )
        	        {
        	            m_weightsHiddenOutput[HiddenOutputIdx] = weights[weightIdx];
        	            weightIdx++;
        	        }
        	}
    }

    void Network::LoadWeightsFromBuffer(std::vector<double> const & weights)
    {
		int32_t  numInputHiddenWeights = m_numInputs * m_numHidden;
	    int32_t  numHiddenOutputWeights = m_numHidden * m_numOutputs;
	    assert( weights.size() == (unsigned int)(numInputHiddenWeights + numHiddenOutputWeights));

	    int32_t weightIdx = 0;
	    for ( auto InputHiddenIdx = 0; InputHiddenIdx < numInputHiddenWeights; InputHiddenIdx++ )
	        {
	            m_weightsInputHidden[InputHiddenIdx] = weights[weightIdx];
	            weightIdx++;
	        }

	    for ( auto HiddenOutputIdx = 0; HiddenOutputIdx < numHiddenOutputWeights; HiddenOutputIdx++ )
	        {
	            m_weightsHiddenOutput[HiddenOutputIdx] = weights[weightIdx];
	            weightIdx++;
	        }
    }

    void Network::SaveNeuronsIntoFile() const
    {
    	std::fstream file;
    	file.open( neurons_file_name, std::ios::in | std::ios::out | std::ios::trunc );

    	if(file.good() == true)
    		{
    			file << "Input Neurons Values:" << std::endl;
    			for(unsigned int i = 0; i <= m_inputNeurons.size() - 1; i++)
    				file << m_inputNeurons[i] << std::endl;

    			file << "Hidden Neurons Values:" << std::endl;
    			for(unsigned int i = 0; i <= m_hiddenNeurons.size() - 1; i++)
    				file << m_hiddenNeurons[i] << std::endl;

    			file << "Output Neurons Values:" << std::endl;
    			for(unsigned int i = 0; i <= m_outputNeurons.size() - 1; i++)
    				file << m_outputNeurons[i] << std::endl;

    			file.close();
    		}
    }

    void Network::InitializeNetwork()
    {
        // Create storage and initialize the neurons and the outputs
        //-------------------------------------------------------------------------

        // Add bias neurons
        int32_t const totalNumInputs = m_numInputs + 1;
        int32_t const totalNumHiddens = m_numHidden + 1;

        m_inputNeurons.resize( totalNumInputs );
        m_hiddenNeurons.resize( totalNumHiddens );
        m_outputNeurons.resize( m_numOutputs );
        m_clampedOutputs.resize( m_numOutputs );

        memset( m_inputNeurons.data(), 0, m_inputNeurons.size() * sizeof( double ) );
        memset( m_hiddenNeurons.data(), 0, m_hiddenNeurons.size() * sizeof( double ) );
        memset( m_outputNeurons.data(), 0, m_outputNeurons.size() * sizeof( double ) );
        memset( m_clampedOutputs.data(), 0, m_clampedOutputs.size() * sizeof( int32_t ) );

        // Set bias values
        m_inputNeurons.back() = -1.0;
        m_hiddenNeurons.back() = -1.0;

        // Create storage and initialize and layer weights
        //-------------------------------------------------------------------------

        int32_t const numInputHiddenWeights = totalNumInputs * totalNumHiddens;
        int32_t const numHiddenOutputWeights = totalNumHiddens * m_numOutputs;
        m_weightsInputHidden.resize( numInputHiddenWeights );
        m_weightsHiddenOutput.resize( numHiddenOutputWeights );
    }

    void Network::InitializeWeights()
    {
        std::random_device rd;
        std::mt19937 generator( rd() );

        double const distributionRangeHalfWidth = ( 2.4 / m_numInputs );
        double const standardDeviation = distributionRangeHalfWidth * 2 / 6;
        std::normal_distribution<> normalDistribution( 0, standardDeviation );

        // Set weights to normally distributed random values between [-2.4 / numInputs, 2.4 / numInputs]
        for ( int32_t inputIdx = 0; inputIdx <= m_numInputs; inputIdx++ )
        {
            for ( int32_t hiddenIdx = 0; hiddenIdx < m_numHidden; hiddenIdx++ )
            {
                int32_t const weightIdx = GetInputHiddenWeightIndex( inputIdx, hiddenIdx );
                double const weight = normalDistribution( generator );
                m_weightsInputHidden[weightIdx] = weight;
            }
        }

        // Set weights to normally distributed random values between [-2.4 / numInputs, 2.4 / numInputs]
        for ( int32_t hiddenIdx = 0; hiddenIdx <= m_numHidden; hiddenIdx++ )
        {
            for ( int32_t outputIdx = 0; outputIdx < m_numOutputs; outputIdx++ )
            {
                int32_t const weightIdx = GetHiddenOutputWeightIndex( hiddenIdx, outputIdx );
                double const weight = normalDistribution( generator );
                m_weightsHiddenOutput[weightIdx] = weight;
            }
        }
    }

    std::vector<int32_t> const& Network::Evaluate( std::vector<double> const& input )
    {
        assert( input.size() == (unsigned int)m_numInputs );
        assert( m_inputNeurons.back() == -1.0 && m_hiddenNeurons.back() == -1.0 );

        // Set input values
        //-------------------------------------------------------------------------

        memcpy( m_inputNeurons.data(), input.data(), input.size() * sizeof( double ) );

        // Update hidden neurons
    	//-------------------------------------------------------------------------

    	for ( int32_t hiddenIdx = 0; hiddenIdx < m_numHidden; hiddenIdx++ )
    		{
    	     	 m_hiddenNeurons[hiddenIdx] = 0;

    	     	 // Get weighted sum of pattern and bias neuron
    	         for ( int32_t inputIdx = 0; inputIdx <= m_numInputs; inputIdx++ )
    	            {
    	                int32_t const weightIdx = GetInputHiddenWeightIndex( inputIdx, hiddenIdx );
    	                m_hiddenNeurons[hiddenIdx] += m_inputNeurons[inputIdx] * m_weightsInputHidden[weightIdx];
    	            }

    	         // Apply activation function
    	         m_hiddenNeurons[hiddenIdx] = SigmoidActivationFunction( m_hiddenNeurons[hiddenIdx] );
    	    }

        // Calculate output values - include bias neuron
        //-------------------------------------------------------------------------

        for ( int32_t outputIdx = 0; outputIdx < m_numOutputs; outputIdx++ )
        {
            m_outputNeurons[outputIdx] = 0;

            // Get weighted sum of pattern and bias neuron
            for ( int32_t hiddenIdx = 0; hiddenIdx <= m_numHidden; hiddenIdx++ )
            {
                int32_t const weightIdx = GetHiddenOutputWeightIndex( hiddenIdx, outputIdx );
                m_outputNeurons[outputIdx] += m_hiddenNeurons[hiddenIdx] * m_weightsHiddenOutput[weightIdx];
            }

            // Apply activation function and clamp the result
            m_outputNeurons[outputIdx] = SigmoidActivationFunction( m_outputNeurons[outputIdx] );
            m_clampedOutputs[outputIdx] = ClampOutputValue( m_outputNeurons[outputIdx] );
        }

        return m_clampedOutputs;
    }
}
