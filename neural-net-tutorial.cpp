#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

// Get connection containing weight
struct Connection
{
    double weight;
    double deltaWeight;
};

// Neuron class
class Neuron
{
private:
    double m_output_value;
    vector<Connection> m_output_weights;
    static double randomWeight()
    {
        return rand() / double(RAND_MAX);
    };

public:
    Neuron(unsigned num_outputs);
    double setOuputValue(double val) { m_output_value = val; };
    double getOuputValue() { return m_output_value; };
    void feedForward(Layer &previous_layer)
    {
        double sum = 0.0;
        for (unsigned current_neurone = 0; current_neurone < previous_layer.size(); current_neurone++)
        {
            sum += previous_layer[current_neurone].m_output_value * previous_layer[current_neurone].m_output_weights[0].weight;
        }
    };
};

// Attributing weight to neural network by getting the next outputs number
Neuron::Neuron(unsigned num_outputs)
{
    for (unsigned connection = 0; connection < num_outputs; connection++)
    {
        //for each next out put create connections
        m_output_weights.push_back(Connection());

        // Adding random weight
        m_output_weights.back().weight = randomWeight();
    }
}
// end Neuron class

// Create multiple layers containing neuron
typedef vector<Neuron> Layer;

class Net
{
private:
    // Create multiple layers containing all layer
    vector<Layer> m_layers;

public:
    Net(const vector<unsigned> &topology);
    void feedForward(const vector<double> &inputsVals);
    void backProp(const vector<double> &targetVals);
    void getResults(vector<double> &resultVals);
};

// Creation of constructor who attribute layer to neuralnet and neuron to this neural network
Net::Net(const vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();

    for (unsigned current_layer = 0; current_layer < numLayers; current_layer++)
    {
        m_layers.push_back(Layer());

        for (unsigned i = 0; i <= topology[current_layer]; i++)
        {
            if (current_layer == topology.size() - 1)
            {
                m_layers.back().push_back(Neuron(topology[current_layer + 1]));
            }
            else
            {
                m_layers.back().push_back(Neuron(0));
            }
            printf("Neurone created\n");
        }
    }
}

void Net::feedForward(const vector<double> &inputsVals)
{
    try
    {
        assert(inputsVals.size() == m_layers.size() - 1);
    }
    catch (unsigned)
    {
        printf("Please check the size of your inputs vector");
    }

    for (unsigned i = 0; i < inputsVals.size(); i++)
    {
        /* code */
        // For heach neurone atach value to neurone
        m_layers[0][i].setOuputValue(inputsVals[i]);
    }

    // Go forward into layers neurone;
    for (unsigned current_layers = 0; current_layers < m_layers.size(); current_layers++)
    {

        for (unsigned current_neurone = 0; current_neurone < m_layers[current_layers].size(); current_neurone++)
        {
            m_layers[current_layers][current_neurone].feedForward(&m_layers[current_layers - 1]);
        }
    }
}

int main()
{
    vector<unsigned> topology;

    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);

    Net myNet(topology);
    // vector<double> inputsVals;
    // myNet.feedForward(inputsVals);

    // vector<double> targetVals;
    // myNet.backProp(targetVals);

    // vector<double> resultVals;
    // myNet.getResults(resultVals);
}
