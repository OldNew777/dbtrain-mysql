#include "column.h"

#include "exception/exceptions.h"

namespace dbtrain_mysql {

Column::Column(const String& sName, FieldType iType, bool CanBeNull, 
   const Size& nSize, bool isPrimary)
    : _sName(sName), _iType(iType), _CanBeNull(CanBeNull),
     _nSize(nSize), _IsPrimary(isPrimary) {}
Column::Column(const std::vector<std::vector<String> >& sPKVec, 
    const std::vector<String>& sPKNameVec,
    const std::vector<std::vector<std::vector<String> > >& sFKVec,
    const std::vector<String>& sFKNameVec
  ): _PKVec(sPKVec) ,_sPKNameVec(sPKNameVec), 
   _FKVec(sFKVec) ,_sFKNameVec(sFKNameVec)
  {}

String Column::GetName() const { return _sName; }
FieldType Column::GetType() const { return _iType; }
Size Column::GetSize() const { return _nSize; }
bool Column::GetCanBeNull() const {return _CanBeNull;}
bool Column::GetIsPrimary() const {return _IsPrimary;}

std::vector<String> Column::GetPKNameVec() const{return _sPKNameVec;}
std::vector<String> Column::GetFKNameVec() const{return _sFKNameVec;}
std::vector<std::vector<String> > Column::GetPKVec() const{return _PKVec;}
std::vector<std::vector<std::vector<String> > > Column::GetFKVec() const{return _FKVec;}

void Column::Show() const{
   if(_sName != ""){
      printf("%s\t%d\t%d\n", _sName.data(), _iType, 
         _CanBeNull); 
   }else{
      printf("\nprimary key\n");
      for(int i = 0; i < _PKVec.size(); i ++){
         if(_sPKNameVec[i] == "")
            printf("No Name: " );
         else
            printf("%s: ", _sPKNameVec[i].data());
         printf("{ ");
         for(auto& pk: _PKVec[i]){
            printf("%s ", pk.data());
         }
         printf("}\n");
      }
      printf("\nforeign key:\n");
      for(int i = 0; i < _FKVec.size(); i ++){
         if(_sFKNameVec[i] == "")
            printf("No Name:\n");
         else
            printf("%s: ", _sFKNameVec[i].data());
         printf("{\n");
         for(auto& pk: _FKVec[i]){
            printf("\t{ %s %s %s }\n",
            pk[0].data(), pk[1].data(), pk[2].data());
         }
         printf("}\n");
      }
      
   }
}
}  // namespace dbtrain_mysql
