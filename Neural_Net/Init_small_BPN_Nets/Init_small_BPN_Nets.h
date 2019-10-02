/*
 * Initialize_small_BPN_Nets.h
 *
 *  Created on: 28 gru 2018
 *      Author: damian
 */

#ifndef INIT_SMALL_BPN_NETS_INIT_SMALL_BPN_NETS_H_
#define INIT_SMALL_BPN_NETS_INIT_SMALL_BPN_NETS_H_

#include "../BPN_NeuralNetwork/NeuralNetworkTrainer.h"
#include "../BPN_NeuralNetwork/TrainingDataReader.h"

using namespace std;
using namespace BPN;

class Initialize_small_BPN_Networks
{
	private:
		unsigned int ok;
		fstream file;
		string tmp;
		string tmp1;

		const string directory_path;
		const string map_f = "map_file.txt";
		const string Trainer_Logger_f = "TrainerLogger.txt";
		const string neurons_f = "neurons.txt";
		const string config_f = "config.txt";
		const string weights_f = "weights.txt";
		const string set_f = "sets.txt";

		Network::Settings networkSettings;
		NetworkTrainer::Settings trainerSettings;

		vector<string> names{"Input_Neurons=", "Hidden_Neurons=", "Output_Neurons=", "Max_Epochs=",
			"Learning_Rate=", "Momentum=", "desiredAccuracy=", "Use_BatchLearning=false", "Use_BatchLearning=true"};

		vector<uint32_t *> wsk{&networkSettings.m_numInputs, &networkSettings.m_numHidden, &networkSettings.m_numOutputs,
			&trainerSettings.m_maxEpochs};

		vector<double *> wsk1{&trainerSettings.m_learningRate, &trainerSettings.m_momentum, &trainerSettings.m_desiredAccuracy};

		void upload_values(string directory, string neurons, string weights, string Trainer_Logger);

	public:
		vector< vector<double> > buffer_weights;

		vector<Network::Settings> NetworkSettings;
		vector <NetworkTrainer::Settings> TrainerSettings;

		void update_map_files(string directory);
		void load_weights_from_file(string directory, vector< vector<double> > *buffer_weights);

	public:
		vector<string> Network_name;
		vector<string> Network_directory;
		vector<string> Trainer_Logger_directory;
		vector<string> neurons_directory;
		vector<string> config_directory;
		vector<string> weights_directory;
		vector<string> set_directory;

		Initialize_small_BPN_Networks(string dp);

		void search_networks(ostream & os);
		void check_files(ostream & os);
		void initialize_values(ostream & os);
		void train_network(string network_name);
};

#endif /* INIT_SMALL_BPN_NETS_INIT_SMALL_BPN_NETS_H_ */
