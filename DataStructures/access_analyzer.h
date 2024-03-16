#pragma once

#include <complexities/complexity_analyzer.h>
#include "../DataStructures/libds/adt/list.h"
#include "../DataStructures/libds/adt/array.h"
#include <iterator>
#include <random>
#include <vector>

namespace ds::utils
{
    /**
     * @brief Common base for list analyzers.
     */
    template<class ADS>
    class AccessAnalyzer : public ComplexityAnalyzer<List>
    {
    protected:
        explicit AccessAnalyzer(const std::string& name);

    protected:
        void beforeOperation(ADS& structure) override;
        size_t getRandomIndex() const;
        int getRandomData() const;
        void executeOperation(ADS& structure) override;

    private:
        void insertNElements(ADS& structure, size_t n);

    private:
        std::default_random_engine rngData_;
        std::uniform_int_distribution<std::size_t>* indexDist_;
        size_t index_;
        int data_;
    };


    /**
     * @brief Container for all list analyzers.
     */
    class AccessesAnalyzer : public CompositeAnalyzer
    {
    public:
        AccessesAnalyzer() :
            CompositeAnalyzer("Accesses")
        {
            this->addAnalyzer(std::make_unique<AccessAnalyzer<adt::ImplicitList<int>>>("implicit_list-access"));
            this->addAnalyzer(std::make_unique<AccessAnalyzer<adt::SinglyLinkedList<int>>>("singly_linked_list-access"));
            //this->addAnalyzer(std::make_unique<AccessAnalyzer<adt::Array<int>>>("array-access"));
        }
    };

    template<class ADS>
    inline AccessAnalyzer<ADS>::AccessAnalyzer(const std::string& name)
    {
        ComplexityAnalyzer<List>(name, [this](ADS& ads, size_t size)
            {
                this->insertNElements(ads, size);
            }),
            rngData_(std::random_device()()),
            indexDist_(nullptr),
            index_(0),
            data_(0)
    }

    template<class ADS>
    inline void AccessAnalyzer<ADS>::beforeOperation(ADS& structure)
    {
        this->index_ = this->getRandomIndex();
    }

    template<class ADS>
    inline size_t AccessAnalyzer<ADS>::getRandomIndex() const
    {
        return (*this->indexDist_)();
    }

    template<class ADS>
    inline int AccessAnalyzer<ADS>::getRandomData() const
    {
        return this->rngData_();
    }

    template<class ADS>
    inline void AccessAnalyzer<ADS>::executeOperation(ADS& structure)
    {
        structure.access(this->index_);
    }

    template<class ADS>
    inline void AccessAnalyzer<ADS>::insertNElements(ADS& structure, size_t n)
    {
        for (size_t i = 0; i < n; i++) {
            structure.insertLast(this->getRandomData());
        }

        if (this->indexDist_ != nullptr) {
            return;
        }

        this->indexDist = new std::uniform_int_distribution<std::size_t>(0, structure.size() - 1)
    }
}
