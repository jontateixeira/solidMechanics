/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2004-2007 Hrvoje Jasak
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

Class
    contactProblem

Description
    Class describes a multiple body contact problem.  Each individual contact
    is described by a contactPatchPair.  contactProblem handles
    multiple contact updates and sets the boundary conditions on the
    displacement field.

    For total or incremental strain solver.

SourceFiles
    contactProblem.C

\*---------------------------------------------------------------------------*/

#ifndef contactProblem_H
#define contactProblem_H

#include "contactPatchPairList.H"
#include "IOdictionary.H"
#include "volFields.H"
#include "pointFields.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class fvMesh;

/*---------------------------------------------------------------------------*\
                         Class contactProblem Declaration
\*---------------------------------------------------------------------------*/

class contactProblem
:
    public IOdictionary,
    public contactPatchPairList
{
private:

    // Private data

        //- Reference to displacement field
        volVectorField& U_;

    // Private Member Functions

        //- Disallow default bitwise copy construct
        contactProblem(const contactProblem&);

        //- Disallow default bitwise assignment
        void operator=(const contactProblem&);


public:

    //- Runtime type information
    TypeName("contactProblem");


    // Constructors

        //- Read constructor
        contactProblem
        (
	 volVectorField& U
	 );


    // Destructor

        virtual ~contactProblem()
        {}


    // Member Functions

        //- Return const reference to displacement field
        const volVectorField& U() const
        {
            return U_;
        }

        //- Return reference to displacement field
        volVectorField& U()
        {
            return U_;
        }

        //- Return const reference to mesh
        const fvMesh& mesh() const
        {
            return U_.mesh();
        }


        //- Return contact gap point field
        //tmp<pointScalarField> contactGapPoints() const;
  //- contact problem should be able to write these fields
  //- they don't have to be made in the main program
        void contactGapPoints(pointScalarField& cGapPoints);

        //- Return contact gap point field
        void contactPointForce(pointVectorField& cPointForce);

        //- Return contact area field
        tmp<volScalarField> contactArea() const;

        //- Return contact pressure field
        tmp<volScalarField> contactPressure() const;
        
         //- Return a list of contact patch pair names
         wordList names() const;

         //- Correct contact conditions
         void correct();

         //- Read rheologyProperties dictionary
  //         virtual bool read();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
