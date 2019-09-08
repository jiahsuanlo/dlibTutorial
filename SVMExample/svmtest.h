#ifndef SVMTEST_H
#define SVMTEST_H
#include <dlib/svm.h>
#include <iostream>
#include <QString>

namespace svt
{

class SVMTester
{
public:
    typedef dlib::matrix<double,2,1> sample_type;
    typedef dlib::radial_basis_kernel<sample_type> kernel_type;
    // decision function
    typedef dlib::decision_function<kernel_type> dec_funct_type;
    typedef dlib::normalized_function<dec_funct_type> funct_type;
    // prob decision function
    typedef dlib::probabilistic_decision_function<kernel_type> prob_funct_type;
    typedef dlib::normalized_function<prob_funct_type> pfunc_type;
    SVMTester();

    // utility functions
    void CrossValidationCheck();
    void Train(double C, double gamma);
    void TrainPFunction(double C, double gamma);
    void TestOneSample(const sample_type &samp);

    void SaveModel(const QString &filename);
    void LoadModel(const QString &filename);

    void CrossValidateReduced(int num_vectors, int fold);
    void ReduceModel(int num_vectors, int fold);


private:
    std::vector<sample_type> samples_;
    std::vector<double> labels_;
    dlib::svm_c_trainer<kernel_type> trainer_;
    dlib::vector_normalizer<sample_type> normalizer_;
    funct_type learned_function_;
    pfunc_type learned_pfunction_;


};


}
#endif // SVMTEST_H
