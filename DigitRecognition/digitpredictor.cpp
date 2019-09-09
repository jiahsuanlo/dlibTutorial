#include "digitpredictor.h"

using namespace dlib;

namespace dp {

DigitPredictor::DigitPredictor(const DigitPredictorParams &params):
    trainer_(net_),
    params_(params)
{
    SetTrainerSettings();
}

void DigitPredictor::Train()
{

    // Finally, this line begins training.  By default, it runs SGD with our specified
    // learning rate until the loss stops decreasing.  Then it reduces the learning rate by
    // a factor of 10 and continues running until the loss stops decreasing again.  It will
    // keep doing this until the learning rate has dropped below the min learning rate
    // defined above or the maximum number of epochs as been executed (defaulted to 10000).
    trainer_.train(training_images_, training_labels_);

    // Now let's run the training images through the network.  This statement runs all the
    // images through it and asks the loss layer to convert the network's raw output into
    // labels.  In our case, these labels are the numbers between 0 and 9.
    std::vector<unsigned long> predicted_labels = net_(training_images_);
    int num_right = 0;
    int num_wrong = 0;
    // And then let's see if it classified them correctly.
    for (size_t i = 0; i < training_images_.size(); ++i)
    {
        if (predicted_labels[i] == training_labels_[i])
            ++num_right;
        else
            ++num_wrong;

    }

    // clean model to reduce size
    net_.clean();

    std::cout << "training num_right: " << num_right << "\n";
    std::cout << "training num_wrong: " << num_wrong << "\n";
    std::cout << "training accuracy:  " << num_right/double(num_right+num_wrong) <<"\n";

}

void DigitPredictor::LoadData(const QString &data_dir)
{
    // MNIST is broken into two parts, a training set of 60000 images and a test set of
    // 10000 images.  Each image is labeled so that we know what hand written digit is
    // depicted.  These next statements load the dataset into memory.

    // use dlib mnist load data function to load mnist data
    dlib::load_mnist_dataset(data_dir.toStdString(),
                             training_images_, training_labels_,
                             testing_images_, testing_labels_);

    std::cout<<"Mnist Data loaded successfully!!\n";
}

void DigitPredictor::SaveModel(const QString &filename)
{
    dlib::serialize(filename.toStdString())<< net_;

    std::cout<<"Model is saved as "<< filename.toStdString()<<"\n";
}

DigitPredictorParams &DigitPredictor::Params()
{
    return params_;
}

void DigitPredictor::SetTrainerSettings()
{
    trainer_.set_learning_rate(params_.learning_rate);
    trainer_.set_min_learning_rate(params_.mini_learning_rate);
    trainer_.set_mini_batch_size(params_.minibatch_size);
    if (params_.trainer_verbose)
        trainer_.be_verbose();
    // Since DNN training can take a long time, we can ask the trainer to save its state to
    // a file named "mnist_sync" every 20 seconds.  This way, if we kill this program and
    // start it again it will begin where it left off rather than restarting the training
    // from scratch.  This is because, when the program restarts, this call to
    // set_synchronization_file() will automatically reload the settings from mnist_sync if
    // the file exists.
    trainer_.set_synchronization_file(params_.sync_filename,
                                     std::chrono::seconds(params_.sync_sec));
}


}
