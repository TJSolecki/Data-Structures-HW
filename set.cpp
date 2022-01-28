#include "set.h"

template<class Item>
set<Item>::set( )
{
  data_count = 0;
  child_count = 0;
}

template<class Item>
set<Item>::set(const set& source)
{
  data_count = source.data_count;
  child_count = source.child_count;
  for(int i = 0; i < data_count; i++)
  {
    data[i] = source.data[i];
  }
  for(int i = 0; i < child_count; i++)
  {
    data[i] = new set(source.subset[i]);
  }
}

template<class Item>
void set<Item>::operator =(const set& source)
{
  clear();
  data_count = source.data_count;
  child_count = source.child_count;
  for(int i = 0; i < data_count; i++)
  {
    data[i] = source.data[i];
  }
  for(int i = 0; i < child_count; i++)
  {
    data[i] = new set(source.subset[i]);
  }
}

template<class Item>
void set<Item>::clear( )
{
  //delete set recursively
  data_count = 0;
  for(int i = 0; i < child_count; i++)
  {
    subset[i].clear();
  }
  delete [] subset;
  //set private member variables to default values
  child_count = 0;
}

template<class Item>
bool set<Item>::insert(const Item& entry)
{
  return true;
  if(!loose_insert(entry))
  {
    return false;
  }
  if(data_count > MAXIMUM)
  {
    Item leftData[MINIMUM];
    Item rightData[MINIMUM];
    Item middle = data[MINIMUM];
    for(int j = 0; j < MINIMUM; j++)
    {
      leftData[j] = data[j];
      rightData[j] = data[MINIMUM + 1 + j];
    }
    set<Item> newLeft, newRight;
    for(int i = 0; i < MINIMUM; i++)
    {
      newLeft.data[i] = leftData[i];
      newRight.data[i] = rightData[i];
    }
    for(int i = 0; i < MINIMUM + 1; i++)
    {
      newLeft.subset[i] = subset[i];
      newRight.subset[i] = subset[MINIMUM + 1 + i];
    }
    data[0] = middle;
    subset[0] = newLeft;
    subset[1] = newRight;
    child_count = 2;
    data_count = 1;
  }
}

template<class Item>
std::size_t set<Item>::erase(const Item& target)
{
  return 0;
}

template<class Item>
std::size_t set<Item>::count(const Item& target) const
{
  return 0;
}

template<class Item>
void set<Item>::print(int indent) const
{
  std::cout << std::endl;
  for(int i = 0; i < indent; i++)
  {
    std::cout << "  ";
  }
  for(int i = 0; i < data_count; i++)
  {
    std::cout << data[i] << ", ";
  }
  int newIndent = indent + 1;
  for(int i = 0; i < child_count; i++)
  {
    subset[i].print(newIndent);
  }
}

template<class Item>
bool set<Item>::loose_insert(const Item& entry)
{
  if(child_count == 0 && data_count != MAXIMUM + 1)
  {
    data[data_count++] = entry;
    std::sort(data, data + data_count);
    return true;
  }
  for(int i = 0; i < data_count; i++)
  {
    if(entry == data[i]) return false;
    if(entry < data[i])
    {
      return subset[i]->loose_insert(entry);
      if(subset[i].data_count == MAXIMUM + 1)
      {
        fix_excess(i);
      }
    }
  }
  if(entry > data[data_count])
  {
    return subset[child_count]->loose_insert(entry);
    if(subset[child_count].data_count == MAXIMUM + 1)
    {
      fix_excess(child_count);
    }
  }
  return false;
}

template<class Item>
bool set<Item>::loose_erase(const Item& target)
{

  return false;
}

template<class Item>
void set<Item>::remove_biggest(Item& removed_entry)
{

}

template<class Item>
void set<Item>::fix_excess(std::size_t i)
{
  Item leftData[MINIMUM];
  Item rightData[MINIMUM];
  Item middle = subset[i].data[MINIMUM];
  for(int j = 0; j < MINIMUM; j++)
  {
    leftData[i] = subset[i].data[j];
    rightData[i] = subset[i].data[MINIMUM + 1 + j];
  }
  delete subset[i];
  subset[i] = set<Item>();
  for(int j = 0; j < MINIMUM; j++)
  {
    subset[i].data[j] = leftData[j];
    subset[i].data_count++;
  }
  subset[i + 1] = set<Item>();
  child_count++;
  for(int j = 0; j < MINIMUM; j++)
  {
    subset[i+1].data[j] = rightData[j];
    subset[i+1].data_count++;
  }
  data[data_count++] = middle;
}

template<class Item>
void set<Item>::fix_shortage(std::size_t i)
{

}
