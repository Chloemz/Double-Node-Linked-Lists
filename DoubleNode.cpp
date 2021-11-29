/** @author: Chloe Marie

DoubleNode.cpp: Implements DoubleNode & DoublyLinkedList functions using Templates, ADTs, and recursion 
*/

/** Implementation file for the class ItemType
 @file DoublyLinkedList.cpp */
//Note: #included DoubleNode.cpp in the hpp => test file only needs to include the hpps

/** Default constructor sets next_ and prev_ to @param nullptr
*/
template<class ItemType>
DoubleNode<ItemType>::DoubleNode() : next_(nullptr), prev_(nullptr)
{

}//end default constructor 

/** Constructor sets item_ = @param anItem, next_ = @param nextNodePtr,& prev_ = @param previousNodePtr
*/
template<class ItemType>
DoubleNode<ItemType>::DoubleNode(const ItemType &anItem, DoubleNode<ItemType> *nextNodePtr, DoubleNode<ItemType> *previousNodePtr) : item_(anItem), next_(nextNodePtr), prev_(previousNodePtr)
{

}//end constructor

/** @post: sets item_ @param anItem 
*/
template<class ItemType>
void DoubleNode<ItemType>::setItem(const ItemType &anItem) 
{
    item_ = anItem;
}//end setItem

/** @post: sets prev_ = @param previousNodePtr 
*/
template<class ItemType>
void DoubleNode<ItemType>::setPrevious(DoubleNode<ItemType> *previousNodePtr) //sets prev_ equal to previousNodePtr parameter
{
    prev_ = previousNodePtr;
}//end setPrevious

/** @post: sets next_ = @param nextNodePtr 
*/
template<class ItemType>
void DoubleNode<ItemType>::setNext(DoubleNode<ItemType> *nextNodePtr)//sets next_ equal to nextNodePtr parameter
{
    next_ = nextNodePtr;
}//end setNext

/** @return item_
*/
template<class ItemType>
ItemType DoubleNode<ItemType>::getItem() const//returns item_
{
    return item_;
}//end getItem

/** @return next_
*/
template<class ItemType>
DoubleNode<ItemType> *DoubleNode<ItemType>::getNext() const 
{
    return next_;
}//end getNext

/** @return prev_
*/
template<class ItemType>
DoubleNode<ItemType> *DoubleNode<ItemType>::getPrevious() const //returns prev_
{
    return prev_;
}//end getPrevious
