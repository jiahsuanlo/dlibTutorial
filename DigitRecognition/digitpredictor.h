#ifndef DIGITPREDICTOR_H
#define DIGITPREDICTOR_H

#include <QString>
#include <iostream>

#include <dlib/dnn.h>
#include <dlib/data_io.h>

namespace dp {

// network model definition
// Now let's define the LeNet.  Broadly speaking, there are 3 parts to a network
// definition.  The loss layer, a bunch of computational layers, and then an input
// layer.  You can see these components in the network definition below.
//
// The input layer here says the network expects to be given matrix<unsigned char>
// objects as input.  In general, you can use any dlib image or matrix type here, or
// even define your own types by creating custom input layers.
//
// Then the middle layers define the computation the network will do to transform the
// input into whatever we want.  Here we run the image through multiple convolutions,
// ReLU units, max pooling operations, and then finally a fully connected layer that
// converts the whole thing into just 10 numbers.
//
// Finally, the loss layer defines the relationship between the network outputs, our 10
// numbers, and the labels in our dataset.  Since we selected loss_multiclass_log it
// means we want to do multiclass classification with our network.   Moreover, the
// number of network outputs (i.e. 10) is the number of possible labels.  Whichever
// network output is largest is the predicted label.  So for example, if the first
// network output is largest then the predicted digit is 0, if the last network output
// is largest then the predicted digit is 9.
using namespace dlib;


// ==== NetWork Model ====
// This net_type defines the entire network architecture.  For example, the block
// relu<fc<84,SUBNET>> means we take the output from the subnetwork, pass it through a
// fully connected layer with 84 outputs, then apply ReLU.  Similarly, a block of
// max_pool<2,2,2,2,relu<con<16,5,5,1,1,SUBNET>>> means we apply 16 convolutions with a
// 5x5 filter size and 1x1 stride to the output of a subnetwork, then apply ReLU, then
// perform max pooling with a 2x2 window and 2x2 stride.
using conv1= max_pool<2,2,2,2, relu<con<6,5,5,1,1, input<matrix<unsigned char>>>>>;
using conv2= max_pool<2,2,2,2, relu<con<16,5,5,1,1, conv1>>>;
using fc1= relu<fc<120, conv2>>;
using fc2= relu<fc<84, fc1>>;
using outlayer= fc<10, fc2>;
using net_type= loss_multiclass_log<outlayer>;
/*using net_type = loss_multiclass_log<
                            fc<10,
                            relu<fc<84,
                            relu<fc<120,
                            max_pool<2,2,2,2,relu<con<16,5,5,1,1,
                            max_pool<2,2,2,2,relu<con<6,5,5,1,1,
                            input<matrix<unsigned char>>
                            >>>>>>>>>>>>;*/

struct DigitPredictorParams
{
    double learning_rate= 0.01;
    double mini_learning_rate= 0.00001;
    unsigned long minibatch_size= 128;
    bool trainer_verbose= true;
    std::string sync_filename= "mnist_sync";
    int sync_sec= 20;
};

class DigitPredictor
{
public:
    DigitPredictor(const DigitPredictorParams &params);

    void Train();

    void EvaluateTrainingSet();
    void EvaluateTestSet();

    // Utitlity Functions
    void LoadData(const QString &data_dir);
    void LoadModel(const QString &filename);
    void SaveModel(const QString &filename);

    // Getters
    DigitPredictorParams& Params();

    // Setter
    void SetTrainerSettings();

private:
    std::vector<dlib::matrix<unsigned char>> training_images_;
    std::vector<unsigned long>         training_labels_;
    std::vector<dlib::matrix<unsigned char>> testing_images_;
    std::vector<unsigned long>         testing_labels_;

    net_type net_;
    dlib::dnn_trainer<net_type> trainer_;
    DigitPredictorParams params_;

};

}
#endif // DIGITPREDICTOR_H
