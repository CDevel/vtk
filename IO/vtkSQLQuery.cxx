/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkSQLQuery.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*-------------------------------------------------------------------------
  Copyright 2008 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------*/
#include "vtkSQLQuery.h"

#include "vtkObjectFactory.h"
#include "vtkSQLDatabase.h"
#include "vtkVariantArray.h"

#include "vtksys/SystemTools.hxx"

vtkCxxRevisionMacro(vtkSQLQuery, "$Revision: 1.5 $");

vtkSQLQuery::vtkSQLQuery()
{
  this->Query = 0;
  this->Database = 0;
  this->Active = false;
}

vtkSQLQuery::~vtkSQLQuery()
{
  this->SetQuery(0);
  if (this->Database)
    {
    this->Database->Delete();
    this->Database = NULL;
    }
}

vtkCxxSetObjectMacro(vtkSQLQuery, Database, vtkSQLDatabase);

void vtkSQLQuery::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "Query: " << (this->Query ? this->Query : "NULL") << endl;
  os << indent << "Database: " << (this->Database ? "" : "NULL") << endl;
  if (this->Database)
    {
    this->Database->PrintSelf(os, indent.GetNextIndent());
    }
}

vtkStdString vtkSQLQuery::EscapeString( vtkStdString s, bool addSurroundingQuotes )
{
  vtkStdString d;
  if ( addSurroundingQuotes )
    {
    d += '\'';
    }

  for ( vtkStdString::iterator it = s.begin(); it != s.end(); ++ it )
    {
    if ( *it == '\'' )
      d += '\''; // Single quotes are escaped by repeating them
    d += *it;
    }

  if ( addSurroundingQuotes )
    {
    d += '\'';
    }
  return d;
}

char* vtkSQLQuery::EscapeString( const char* src, bool addSurroundingQuotes )
{
  vtkStdString sstr( src );
  vtkStdString dstr = this->EscapeString( sstr, addSurroundingQuotes );
  return vtksys::SystemTools::DuplicateString( dstr.c_str() );
}
