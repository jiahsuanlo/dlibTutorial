#include "svmtest.h"

namespace svt {


SVMTester::SVMTester()
{
    // initialize data
    // add some data
    for (int r = -20; r <= 20; ++r)
    {
        for (int c = -20; c <= 20; ++c)
        {
            sample_type samp;
            samp(0) = r;
            samp(1) = c;
            samples_.push_back(samp);

            // if this point is less than 10 from the origin
            if (sqrt(double(r*r) + c*c) <= 10)
                labels_.push_back(+1);
            else
                labels_.push_back(-1);
        }
    }

    // normalize by (x-mean)/std
    normalizer_.train(samples_);

    for(size_t i=0; i<samples_.size(); ++i)
    {
        samples_[i]= normalizer_(samples_[i]);
    }

    // randomize samples
    dlib::randomize_samples(samples_, labels_);
}

void SVMTester::CrossValidationCheck()
{
    // check diiferent c and gamma values
    std::cout << "doing cross validation" << "\n";
    for (double gamma = 0.00001; gamma <= 1; gamma *= 5)
    {
        for (double C = 1; C < 100000; C *= 5)
        {
            // tell the trainer the parameters we want to use
            trainer_.set_kernel(kernel_type(gamma));
            trainer_.set_c(C);

            std::cout << "gamma: " << gamma << "    C: " << C;
            // Print out the cross validation accuracy for 3-fold cross validation using
            // the current gamma and C.  cross_validate_trainer() returns a row vector.
            // The first element of the vector is the fraction of +1 training examples
            // correctly classified and the second number is the fraction of -1 training
            // examples correctly classified.
            std::cout << "     cross validation accuracy: "
                 << dlib::cross_validate_trainer(trainer_, samples_, labels_, 3);
        }
    }

    std::cout<<"done with cross validation...\n";
}

void SVMTester::Train(double C, double gamma)
{
    trainer_.set_c(C);
    trainer_.set_kernel(kernel_type(gamma));

    learned_function_.normalizer= normalizer_;
    learned_function_.function= trainer_.train(samples_, labels_);

    std::cout << "\nnumber of support vectors in our learned_function is "
             << learned_function_.function.basis_vectors.size() << "\n";

}

void SVMTester::TrainPFunction(double C, double gamma)
{
    trainer_.set_c(C);
    trainer_.set_kernel(kernel_type(gamma));

    learned_pfunction_.normalizer= normalizer_;
    learned_pfunction_.function= dlib::train_probabilistic_decision_function(trainer_,
                                                                             samples_,
                                                                             labels_,3);
    std::cout << "\nnumber of support vectors in our learned_pfunct is "
             << learned_pfunction_.function.decision_funct.basis_vectors.size() << "\n";


}

void SVMTester::TestOneSample(const SVMTester::sample_type &samp)
{
    std::cout<<"The classifier output is:" << learned_function_(samp)<<"\n";
    std::cout<<"The classifier probability output is:" << learned_pfunction_(samp)<<"\n";

}

void SVMTester::SaveModel(const QString &filename)
{
    dlib::serialize(filename.toStdString())<< learned_function_ << learned_pfunction_;

}

void SVMTester::LoadModel(const QString &filename)
{
    dlib::deserialize(filename.toStdString())>> learned_function_ >> learned_pfunction_;
}

void SVMTester::CrossValidateReduced(int num_vectors, int fold)
{
    std::cout << "\ncross validation accuracy with only "<<num_vectors<<" support vectors: "
             << dlib::cross_validate_trainer(dlib::reduced2(trainer_, num_vectors), samples_, labels_, fold);

    // Let's print out the original cross validation score too for comparison.
    std::cout << "cross validation accuracy with all the original support vectors: "
         << dlib::cross_validate_trainer(trainer_, samples_, labels_, fold);

}

void SVMTester::ReduceModel(int num_vectors, int fold)
{
    learned_function_.function= dlib::reduced2(trainer_,num_vectors).train(samples_, labels_);
    learned_pfunction_.function= dlib::train_probabilistic_decision_function(trainer_, samples_,
                                                                             labels_, fold);

    std::cout<<"\nModel reduction is completed!!!\n";

}

}
