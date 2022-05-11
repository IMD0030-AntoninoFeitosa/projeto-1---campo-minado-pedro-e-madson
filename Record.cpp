#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Record.hpp"

// O que acontece ao inveter o operador para >
bool record_cmp(Record &a, Record &b) {
  return a.milliseconds < b.milliseconds;
}

void sort122(std::vector<Record> &records) {
  for(int k=0;k<records.size();k++){
    int pos = 0;
    for(int i=k+1;i<records.size();i++){
      if(record_cmp(records[i], records[pos])){
        pos = i;
      }
    }
    Record tmp = records[pos];
    records[pos] = records[k];
    records[k] = tmp;
  }
}


std::ostream &operator<<(std::ostream &os, Record const &r) {
  return os << '{' << r.name << ',' << r.milliseconds / 1000.0 << ',' << r.nivel << '}';
}

std::ostream &operator<<(std::ostream &os, std::vector<Record> &vet) {
  os << '<' << std::endl << '\t';
  if (vet.size() > 0) {
    os << vet[0];
  }
  for (int i = 1; i < vet.size(); i++) {
    os << ',' << std::endl << '\t' << vet[i];
  }
  os << std::endl << '>';
  return os;
}

// O que acontece ao remover o &?
void sort(std::vector<Record> &records) {
  std::sort(records.begin(), records.end(), record_cmp);
}

void write_records(std::vector<Record> &records, std::string &file_name) {

  std::ofstream file;
  file.open(file_name.c_str());
  if (file.is_open()) {
    file << records.size() << std::endl;
    for (Record rec : records) {
      file << rec.name << std::endl;
      file << rec.milliseconds << std::endl;
      file << rec.nivel << std::endl;
    }
    file.close();
  }
}

void read_records(std::vector<Record> &records, std::string &file_name) {
  std::ifstream file;
  file.open(file_name.c_str());
  if (file.is_open()) {
    records.clear();
    int size;
    file >> size;
    file.ignore();
    for (int i = 0; i < size; i++) {
      Record rec;
      std::getline(file, rec.name);
      file >> rec.milliseconds;
      file >> rec.nivel;
      file.ignore();
      records.push_back(rec);
    }
    file.close();
  }
}

// Alocação dinâmica de memória

void write(char * file_name, int n, Record ** vector){

  std::ofstream file;
  file.open(file_name);
  if (file.is_open()) {
    for (int i=0;i<n;i++) {
      file << vector[i]->name << std::endl;
      file << vector[i]->milliseconds << std::endl;
      file << vector[i]->nivel << std::endl;
    }
    file.close();
  }
}

Record ** read(char * file_name, int & n){
  Record ** vector = new Record*[100];
  std::ifstream file;
  file.open(file_name);
  if (file.is_open()) {
    n = 0;
    while(!file.eof()){
      Record * rec = new Record;
      std::getline(file, rec->name);
      file >> rec->milliseconds;
      file >> rec->nivel;
      file.ignore();
      vector[n++] = rec;
      
      if(n >= 100){
        Record ** bigger = new Record*[n];
        for(int i=0;i<n;i++){
          bigger[i] = vector[i];
        }
        delete [] vector;
        vector = bigger;
      }
    }
    file.close();
  }

  Record ** result = new Record*[n];
  for(int i=0;i<n;i++){
    result[i] = vector[i];
  }
  delete [] vector;
  return result;
}
