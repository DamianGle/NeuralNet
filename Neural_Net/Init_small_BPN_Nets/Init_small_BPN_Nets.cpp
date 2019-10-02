/*
 * Initialize_small_BPN_Networks.cpp
 *
 *  Created on: 5 gru 2018
 *      Author: damian
 */

#include "../Init_small_BPN_Nets/Init_small_BPN_Nets.h"

#include <iostream>
#include <string>
#include <fstream>

#include "../BPN_NeuralNetwork/NeuralNetworkTrainer.h"
#include "../BPN_NeuralNetwork/TrainingDataReader.h"
#include "../Files_Tree/Files_Tree.h"
#include "../PNG/png_common.h"


Initialize_small_BPN_Networks::Initialize_small_BPN_Networks(string dp):directory_path(dp)
{
	ok = 0;
}

void Initialize_small_BPN_Networks::update_map_files(string directory)
{
	Katalog k(directory);

	file.open(directory + '/' + map_f, ios::in | ios::out | ios::trunc);

	if(file.good())
		k.drukuj(file);
	file.close();
}

void Initialize_small_BPN_Networks::load_weights_from_file(string directory, vector< vector<double> > *buffer_weights)
{
	double value;
	vector<double> weights;

    file.open( directory, ios::in | ios::out );
    if(file.good() == true)
    	{
    		file >> value;
    		while(!file.eof())
    			{
    				weights.push_back(value);
    				file >> value;
    			}
    		buffer_weights->push_back(weights);
    		file.close();
    	}
}

void Initialize_small_BPN_Networks::search_networks(ostream & os)
{
	update_map_files(directory_path);

	file.open(directory_path + '/' + map_f, ios::in | ios::out);

	if(file.good())
		{
			file >> tmp;

			while(!file.eof())
				{
					if(tmp.find("Folder:") != string::npos)
						{
							file >> tmp;
							Network_name.push_back(tmp);
						}
					file >> tmp;
				}

			os << "Found " << Network_name.size() << " networks!\n";
			for(unsigned int i = 0; i <= Network_name.size() - 1; i++)
				os << Network_name[i] << '\n';
		}
	file.close();
	os << '\n';
}

void Initialize_small_BPN_Networks::check_files(ostream & os)
{
	vector<string> names = {Trainer_Logger_f, neurons_f, config_f, weights_f, set_f};

	for(unsigned int i = 0; i <= Network_name.size() - 1; i++)
		update_map_files(directory_path + '/' + Network_name[i]);


	for(unsigned int i = 0; i <= Network_name.size() - 1; i++)
		{
			ok = 0;

			file.open(directory_path + '/' + Network_name[i] + '/' + map_f, ios::in | ios::out);

			if(file.good())
				{
					file >> tmp;

					while(!file.eof())
						{
							for(unsigned int i = 0; i <= 4; i++)
								if(tmp.find(names[i]) != string::npos)
									ok++;
							file >> tmp;
						}
				}
			if(ok == 10)
				{
					Network_directory.push_back(directory_path + '/' + Network_name[i]);
					Trainer_Logger_directory.push_back(directory_path + '/' + Network_name[i] + '/' + Trainer_Logger_f);
					neurons_directory.push_back(directory_path + '/' + Network_name[i] + '/' + neurons_f);
					config_directory.push_back(directory_path + '/' + Network_name[i] + '/' + config_f);
					weights_directory.push_back(directory_path + '/' + Network_name[i] + '/' + weights_f);
					set_directory.push_back(directory_path + '/' + Network_name[i] + '/' + set_f);
				}
			else
				{
					os << "Network's files are incomplete! (" << Network_name[i] << ")\n";
					Network_name.erase(Network_name.begin()+i);

					i--;
				}
			file.close();
		}
}

void Initialize_small_BPN_Networks::upload_values(string directory, string neurons, string weights, string Trainer_Logger)
{
	ok = 0;

	file.open(directory, ios::in | ios::out);

	if(file.good())
		{
			file >> tmp;

			while(!file.eof())
				{
					for(unsigned int i  = 0; i <= 8; i++)
						{
							if(tmp.find(names[i]) != string::npos)
								{
								 	ok++;
									for(unsigned int i = 0; i <= tmp.size() - 1; i++)
										if(isdigit(tmp[i]) || tmp[i] == '.') tmp1 += tmp[i];

									if(i<=3) *(wsk[i]) = stoi(tmp1);
									if(i >3 && i < 7) *(wsk1[i-4]) = stod(tmp1);
									if(i == 7) trainerSettings.m_useBatchLearning=false;
									if(i == 8) trainerSettings.m_useBatchLearning=true;

									tmp1.erase(tmp1.begin(), tmp1.end());
								}
						}
					networkSettings.neurons_file_name = neurons;
					networkSettings.weights_file_name = weights;
					trainerSettings.LoggerFileName = Trainer_Logger;

					file >> tmp;
				}
		}
	file.close();
}

void Initialize_small_BPN_Networks::initialize_values(ostream & os)
{
	for(unsigned int i = 0; i <= Network_name.size() - 1; i++)
		{
			upload_values(config_directory[i], neurons_directory[i], weights_directory[i], Trainer_Logger_directory[i]);

			if(ok == 8)
				{
					NetworkSettings.push_back(networkSettings);
					TrainerSettings.push_back(trainerSettings);
				}
			else
				{
					os << "\nConfig file is valid! (" << Network_name[i] << ")\n";

					Network_name.erase(Network_name.begin()+i);
					Network_directory.erase(Network_directory.begin()+i);
					Trainer_Logger_directory.erase(Trainer_Logger_directory.begin()+i);
					neurons_directory.erase(neurons_directory.begin()+i);
					config_directory.erase(config_directory.begin()+i);
					weights_directory.erase(weights_directory.begin()+i);
					set_directory.erase(set_directory.begin()+i);

					i--;
				}
		}

	for(unsigned int i = 0; i <= Network_name.size() - 1; i++)
		{
			load_weights_from_file(weights_directory[i], &buffer_weights);

			os << '\n';
			for(unsigned int z = 0; z <= Trainer_Logger_directory[i].size() + Trainer_Logger_f.size() + 6; z++)
				os << '*';
			os << '\n';

			os << "Network name: " << Network_name[i] << '\n';
			os << "Network directory: " << Network_directory[i] << '\n';
			os << "Logger directory: " << Trainer_Logger_directory[i] << '\n';
			os << "neurons directory: " << neurons_directory[i] << '\n';
			os << "config directory: " << config_directory[i] << '\n';
			os << "weights directory: " << weights_directory[i] << '\n';
			os << "set directory: " << set_directory[i] << '\n';

			os << "\nNetwork settings:\n";
			os << "Input Neurons: " << NetworkSettings[i].m_numInputs << '\n';
			os << "Hidden Neurons: " << NetworkSettings[i].m_numHidden << '\n';
			os << "Outputs Neurons: " << NetworkSettings[i].m_numOutputs << '\n';
			os << "Neurons file name: " << NetworkSettings[i].neurons_file_name << '\n';
			os << "Weights file name: " << NetworkSettings[i].weights_file_name << '\n';

			os << "\nTrainer settings:\n";
			os << "Learning rate: " << TrainerSettings[i].m_learningRate << '\n';
			os << "Momentum: " << TrainerSettings[i].m_momentum << '\n';
			os << "useBatchLearning: " << TrainerSettings[i].m_useBatchLearning << '\n';
			os << "maxEpochs: " << TrainerSettings[i].m_maxEpochs << '\n';
			os << "desiredAccuracy: " << TrainerSettings[i].m_desiredAccuracy << '\n';
			os << "LoggerFileName: " << TrainerSettings[i].LoggerFileName << '\n';
		}
	os << '\n' << Network_name.size() << " networks created\n\n";
}

void Initialize_small_BPN_Networks::train_network(string network_name)
{
	string directory_net = directory_path + '/' + network_name + '/';
	upload_values(directory_net + config_f, directory_net + neurons_f, directory_net + weights_f, directory_net + Trainer_Logger_f);

	Network nn( networkSettings, 0);
	NetworkTrainer trainer( trainerSettings, &nn );

	TrainingDataReader dataReader( directory_net + set_f, networkSettings.m_numInputs, networkSettings.m_numOutputs );

	if ( !dataReader.ReadData() )
	    return;

	trainer.Train( dataReader.GetTrainingData() );

	nn.SaveWeightsIntoFile();
	nn.SaveNeuronsIntoFile();
}
