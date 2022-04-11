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
    if(map->buckets[auxKey] == NULL || map->buckets[auxKey]->value == NULL ||is_equal(map->buckets[auxKey]->key,key) == 1)
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

  /*long cont;
  Pair ** auxBuckets = (Pair **) calloc(map->capacity, sizeof(Pair*));
  if(map != NULL && map->capacity != 0)
  {
    for(cont = 0 ; cont < map->capacity ; cont++)
    {
      if(map->buckets[cont]->key == NULL)
      {
        auxBuckets[cont] = NULL;
      }
      else
      {
      auxBuckets[cont] = map->buckets[cont];
      }
    }

    map->capacity *= 2;
    map->buckets = (Pair **) calloc(map->capacity, sizeof(Pair *));

    for(cont = 0 ; cont < map->capacity ; cont++)
    {
      if(auxBuckets[cont] != NULL)
      {
        insertMap(map,auxBuckets[cont]->key, auxBuckets[cont]->value);
      }
      else
      {
        map->buckets[cont] = NULL;
      }
    }  
  }*/
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
  long auxKey = hash(key, map->capacity);
  long cont = 0;
  if(map != NULL)
  {
    if(map->buckets[auxKey] != NULL && is_equal(map->buckets[auxKey]->key,key) == 1)
    {
      map->buckets[auxKey]->key = NULL;
      map->size--;
    }
    else
    {
      while(cont < map->capacity)
      {
        if(map->buckets[auxKey] == NULL || map->buckets[auxKey]->key == NULL)
        {
          break;
        }
        if(is_equal(map->buckets[auxKey]->key,key) == 1)
        {
          map->buckets[auxKey]->key = NULL;
          map->size--;
          break;
        }
        auxKey++;
        if(auxKey >= map->capacity)
        {
          auxKey = 0;
        }
        cont++;
      }
    }
  }
}

Pair * searchMap(HashMap * map,  char * key) 
{   
  long auxKey = hash(key,map->capacity);
  long cont = 0;
  if(is_equal(map->buckets[auxKey]->key,key) == 1)
  {
    map->current = auxKey;
    return map->buckets[auxKey];
  }
  else
  {
    while(cont < map->capacity)
    {
      if(map->buckets[auxKey] == NULL)
      {
        return NULL;
      }
      if(is_equal(map->buckets[auxKey]->key,key) == 1 )
      {
        return map->buckets[auxKey];
      }
      auxKey++;
      if(auxKey >= map->capacity)
      {
        auxKey = 0;
      }
      cont++;
    }
    return NULL;
  }
}

Pair * firstMap(HashMap * map) 
{
  long aux;

  if(map != NULL)
  {
    for(aux = 0 ; aux < map->capacity; aux++)
    {
      if(map->buckets[aux] != NULL && map->buckets[aux]->key != NULL)
      {
        map->current = aux;
        return map->buckets[aux];
      }
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) 
{
  long aux = map->current + 1;
  long cont;

  if(map != NULL)
  {
    for(cont = 0 ; cont < map->capacity; cont++)
    {
      if(map->buckets[aux] == NULL ||  map->buckets[aux]->key == NULL)
      {
        return NULL;
      }
      if(map->buckets[aux]->key != NULL && map->buckets[aux]->value != NULL)
      {
        map->current = aux;
        return map->buckets[aux];
      }
      if(aux >= map->capacity)
      {
        aux = 0;
      }
      aux++;
    }
    return NULL;
  }
  return NULL;
}
