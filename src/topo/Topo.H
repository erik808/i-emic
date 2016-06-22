//======================================================================
// Author T.E.Mulder --> t.e.mulder@uu.nl
//======================================================================
#ifndef TOPO_H
#define TOPO_H

#include "TopoDecl.H"
#include "GlobalDefinitions.H"

#include <vector>
#include <sstream>

//==================================================================
// constructor
template<typename Model, typename ParameterList>
Topo<Model, ParameterList>::
Topo(Model model, ParameterList pars)
	:
	model_  (model),
	pars_   (pars),
	nMasks_ (pars->get("Number of mask files", 0)),
	delta_  (pars->get("Delta", 0.0))	
{
	INFO("Topo constructor...");
	loadMaskFileNames();
	loadMasks();

	model_->setLandMask(landMasks_[2]);

	// We initialize our vectors with copies of the ones in the model.
	state_ = model_->getState('C');
	rhs_   = model_->getRHS('C');
	sol_   = model_->getSolution('C');

	// Setup indices k,a and b
	k_ = static_cast<int>(std::floor(delta_));
	a_ = std::vector<int>(nMasks_);
	b_ = std::vector<int>(nMasks_);		
	a_[0] = 0;
	b_[0] = 1;
	for (int k = 0; k != nMasks_-1; ++k)
	{
		a_[k+1] = a_[k] + 2 * ((k + 1) % 2);
		b_[k+1] = b_[k] + 2 * ( k % 2 );
	}
	
	INFO("Topo constructor... done");
}

//==================================================================
// constructor
template<typename Model, typename ParameterList>
Topo<Model, ParameterList>::
~Topo()
{
	INFO("Topo destructor");
}

//==================================================================
template<typename Model, typename ParameterList>
void Topo<Model, ParameterList>::loadMaskFileNames()
{
	INFO(" Topo: loading mask files...");
	
	landMaskFileNames_ = std::vector<std::string>(nMasks_);
	std::stringstream fileID;
	for (int i = 0; i != nMasks_; ++i)
	{
		fileID << "Mask file " << i;		
		landMaskFileNames_[i] = pars_->get(fileID.str().c_str(), "");
		assert(landMaskFileNames_[i] != "");
		INFO("  " << fileID.str() << ": " << landMaskFileNames_[i]);
		fileID.str("");
		fileID.clear();
	}
	
	INFO(" Topo: loading mask files... done");
}

//==================================================================
template<typename Model, typename ParameterList>
void Topo<Model, ParameterList>::loadMasks()
{
	INFO(" Topo: loading mask arrays...");

	landMasks_ = std::vector<LandMask>(nMasks_);
	
	for (int i = 0; i != nMasks_; ++i)
	{
		INFO("   loading " << landMaskFileNames_[i]);
		landMasks_[i] = model_->getLandMask(landMaskFileNames_[i]);
	}
	
	INFO(" Topo: loading mask arrays... done");
}

//==================================================================
template<typename Model, typename ParameterList>
double Topo<Model, ParameterList>::getPar()
{
	return delta_;
}

//==================================================================
template<typename Model, typename ParameterList>
void Topo<Model, ParameterList>::setPar(double par)
{
	delta_ = par;
}

//==================================================================
template<typename Model, typename ParameterList>
typename Topo<Model, ParameterList>::VectorPtr
Topo<Model, ParameterList>::getState(char mode)
{
	// TODO
	if (mode == 'V')
	{
		return state_;
	}
	else if (mode == 'C')
	{
		
	}
}

//==================================================================
template<typename Model, typename ParameterList>
typename Topo<Model, ParameterList>::VectorPtr
Topo<Model, ParameterList>::getRHS(char mode)
{
	// TODO
}

//==================================================================
template<typename Model, typename ParameterList>
typename Topo<Model, ParameterList>::VectorPtr
Topo<Model, ParameterList>::getSolution(char mode)
{
	// TODO
}

//==================================================================
template<typename Model, typename ParameterList>
void Topo<Model, ParameterList>::computeRHS()
{
	// TODO
}

//==================================================================
template<typename Model, typename ParameterList>
void Topo<Model, ParameterList>::computeJacobian()
{
	// TODO
}

//==================================================================
template<typename Model, typename ParameterList>
void Topo<Model, ParameterList>::solve(VectorPtr b)
{
	// TODO
}

//==================================================================
template<typename Model, typename ParameterList>
void Topo<Model, ParameterList>::preProcess()
{
	model_->preProcess();
}

//==================================================================
template<typename Model, typename ParameterList>
void Topo<Model, ParameterList>::postProcess()
{
	model_->postProcess();
}

#endif