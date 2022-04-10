#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) 
{
  Pair * newPair = createPair(key, value);
  long auxKey = hash(key, map->capacity);
  long cont = 0;
  if(map != NULL)
  {
    if(map->buckets[auxKey] == NULL || is_equal(map->buckets[auxKey]->key,key) == 1)
    {
      map->buckets[auxKey]= newPair;
      map->size++;
    }
    else
    {
      while(map->buckets[auxKey] != NULL || cont >= map->capacity)
      {
        auxKey++;
        cont++;
        if(auxKey >= map->capacity)
        {
          auxKey = 0;
        }
      }
      if(cont < map->capacity)
      {
        map->buckets[auxKey]= newPair;
        map->size++;
      }
    }
  }
}

void enlarge(HashMap * map) 
{
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap *createMap(long capacity) 
{
  HashMap * mapLocal = (HashMap *) malloc(sizeof(HashMap));

  if (capacity > 0) 
  {
    mapLocal->buckets = (Pair **) calloc(capacity, sizeof(Pair *));
    mapLocal->capacity = capacity;
    mapLocal->current = -1;
    mapLocal->size = 0;
    return mapLocal;
  }
  return NULL;
}

void eraseMap(HashMap * map,  char * key) 
{    


}

Pair * searchMap(HashMap * map,  char * key) 
{   
  long auxKey = hash(key,map->capacity);
  if(is_equal(map->buckets[auxKey]->key,key) == 1)
  {
    map->current = auxKey;
    return map->buckets[auxKey];
  }
  else
  {
    
  }

  return NULL;
}

Pair * firstMap(HashMap * map) 
{
  long aux;

  for(aux = 0 ; aux < map->capacity; aux++)
  {
    if(map->buckets[aux] != NULL)
    {
      map->current = aux;
      return map->buckets[aux];
    }
  }

  return NULL;
}

Pair * nextMap(HashMap * map) 
{
  long aux = map->current + 1;
  long cont;
  for(cont = 0 ; cont < map->capacity; cont++)
  {
    if(aux == map->capacity)
    {
      aux = 0;
    }
    
    if(map->buckets[aux] != NULL)
    {
      map->current = aux;
      return map->buckets[aux];
    }
    aux++;
  }
  return NULL;
}
