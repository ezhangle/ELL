////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     NeuralNetworkPredictorNode.h (nodes)
//  Authors:  Chuck Jacobs, Byron Changuion
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// model
#include "Model.h"
#include "ModelTransformer.h"
#include "Node.h"

// nodes
#include "BatchNormalizationLayerNode.h"
#include "BiasLayerNode.h"

// predictors
#include "NeuralNetworkPredictor.h"

// stl
#include <functional>
#include <string>

namespace ell
{
namespace nodes
{
    /// <summary> A node that represents a neural network. </summary>
    template <typename ValueType>
    class NeuralNetworkPredictorNode : public model::Node
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* inputPortName = "input";
        static constexpr const char* outputPortName = "output";
        const model::InputPort<ValueType>& input = _input;
        const model::OutputPort<ValueType>& output = _output;
        /// @}

        using PredictorType = typename predictors::NeuralNetworkPredictor<ValueType>;
        using Layer = typename predictors::neural::Layer<ValueType>;

        /// <summary> Default Constructor </summary>
        NeuralNetworkPredictorNode();

        /// <summary> Constructor </summary>
        ///
        /// <param name="input"> The signal to predict from </param>
        /// <param name="predictor"> The predictor to use when making the prediction. </param>
        NeuralNetworkPredictorNode(const model::PortElements<ValueType>& input, const PredictorType& predictor);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return "NeuralNetworkPredictorNode"; }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Adds an object's properties to an `Archiver` </summary>
        ///
        /// <param name="archiver"> The `Archiver` to add the values from the object to </param>
        virtual void WriteToArchive(utilities::Archiver& archiver) const override;

        /// <summary> Sets the internal state of the object according to the archiver passed in </summary>
        ///
        /// <param name="archiver"> The `Archiver` to get state from </param>
        virtual void ReadFromArchive(utilities::Unarchiver& archiver) override;

        /// <summary> Makes a copy of this node in the model being constructed by the transformer </summary>
        virtual void Copy(model::ModelTransformer& transformer) const override;

    protected:
        virtual void Compute() const override;
        virtual bool Refine(model::ModelTransformer& transformer) const override;

    private:
        model::Node* AddLayerNode(model::ModelTransformer& transformer, Layer& layer, const model::PortElements<ValueType>& layerInputs) const;

        // Input
        model::InputPort<ValueType> _input;

        // Output
        model::OutputPort<ValueType> _output;

        // Pointer to the predictor
        const PredictorType* _predictor; // Maybe use a shared or unique pointer here, to facilitate moving or copying
    };
}
}

#include "../tcc/NeuralNetworkPredictorNode.tcc"