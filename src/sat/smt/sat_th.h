/*++
Copyright (c) 2020 Microsoft Corporation

Module Name:

    sat_th.h

Abstract:

    Theory plugins

Author:

    Nikolaj Bjorner (nbjorner) 2020-08-25

--*/
#pragma once

#include "util/top_sort.h"
#include "sat/smt/sat_smt.h"
#include "ast/euf/euf_egraph.h"

namespace sat {
    
    class th_internalizer {
    public:
        virtual ~th_internalizer() {}

        virtual literal internalize(expr* e, bool sign, bool root) = 0;


    };

    class th_decompile {
    public:
        virtual ~th_decompile() {}

        virtual bool to_formulas(std::function<expr_ref(sat::literal)>& lit2expr, expr_ref_vector& fmls) = 0;
    };

    class th_model_builder {
    public:

        virtual ~th_model_builder() {}

        /**
           \brief compute the value for enode \c n and store the value in \c values 
           for the root of the class of \c n.
         */
        virtual void add_value(euf::enode* n, expr_ref_vector& values) = 0;

        /**
           \brief compute dependencies for node n
         */
        virtual void add_dep(euf::enode* n, top_sort<euf::enode>& dep) = 0;

        /**
           \brief should function be included in model.
        */
        virtual bool include_func_interp(func_decl* f) const { return false; }
    };


}
