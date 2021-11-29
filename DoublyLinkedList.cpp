/** @author: Chloe Marie
DoublyLinkedList.cpp: Implements DoublyLinkedList & DoubleNode functions using Templates, ADTs, and recursion 
*/

/** Implementation file for the class ItemType
 @file DoublyLinkedList.cpp */
#include <iostream> 
//Note: #included DoublyLinkedList.cpp in the hpp => test file only needs to include the hpps

//default constructor, sets headPtr_ to null and itemCount_ to 0
template <class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList() : headPtr_(nullptr), itemCount_(0)
{

}//end default constructor 

/**
        Copy constructor looks through @param aList and @return /makes a deep copy of the list in the given parameter.
        Traverses(i.e iterates) through the callee list parameter and insert nodes from aList into the caller list (the current one that isn't the parameter)
*/                        
template <class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList(const DoublyLinkedList &aList)
{
    itemCount_ = aList.itemCount_; //set item count = to the item count of the list referenced
    DoubleNode<ItemType>* orig_HeadPtr = aList.headPtr_; //set/save orginal headptr 
    if(orig_HeadPtr == nullptr)//if it reaches the end of the list set the head ptr to null ptr 
    {
        headPtr_ = nullptr;
    }
    else
    {
        headPtr_ = new DoubleNode<ItemType>();//new node 
        headPtr_->setItem(orig_HeadPtr->getItem());//set item in new node list to the item from the original node list 
        DoubleNode<ItemType>* traversePtr = headPtr_;//set traverse ptr to current head ptr
        orig_HeadPtr = orig_HeadPtr->getNext();//set original head pointer to next item on the list 
        while(orig_HeadPtr != nullptr)//while the list isn't empty
        {
            ItemType nextItem = orig_HeadPtr->getItem(); //set next item to the item from original head ptr
            DoubleNode<ItemType>* newNodePtr= new DoubleNode<ItemType>(nextItem); //set new Node ptr to next item on the list
            traversePtr->setNext(newNodePtr);//set ptr to next node on the list ->
            newNodePtr->setPrevious(traversePtr);//set next node on the list to previous-><-
            //move to the next node for copying 
            orig_HeadPtr=orig_HeadPtr->getNext();
            traversePtr=traversePtr->getNext();
        }
    }
}//end copy constructor

//destructor that calls the clear function
template <class ItemType>
DoublyLinkedList<ItemType>::~DoublyLinkedList()
{
    clear();
}//end destructor

/** @return itemCount_
*/
template <class ItemType>
int DoublyLinkedList<ItemType>::getSize() const
{
    return itemCount_;
}//end getSize

/** Finds the node @param pos  
    *Pre: pos is a valid place in the list,
    *Post: @return a pointer to the node at pos, otherwise return nullptr  
*/
template <class ItemType>
DoubleNode<ItemType> *DoublyLinkedList<ItemType>::getAtPos(const int &pos) const
{
    DoubleNode<ItemType>* curPtr = headPtr_;
    for(int i = 1; i < pos; i++)
    {
        curPtr = curPtr->getNext();
    }
    return curPtr;
}//end getAtPos

/** @return *headPtr_
*/
template <class ItemType>
DoubleNode<ItemType> *DoublyLinkedList<ItemType>::getHeadPtr() const
{
    return headPtr_;
}//end getHeadPtr

/**
    Inserts @param item in caller list at @param position
        *NOTE: Position 1 is the first position, not 0
    *Pre: position is a valid place within the list
    *Post: @return true if the item has been inserted in the caller list, otherwise return false 
*/
template<class ItemType>
bool DoublyLinkedList<ItemType>::insert(const ItemType &item, const int &position)
{
   //can Insert if position is within range >=1 & the placemment isn't too far ahead on the list
   bool canInsert = (position >= 1 && position <= itemCount_+1); //Case0: Handles edge case of an invalid position parameter
   if(canInsert)
   {
        DoubleNode<ItemType>* tail_ptr = getAtPos(itemCount_); //set tail ptr 
        DoubleNode<ItemType>* new_NodePtr = new DoubleNode<ItemType>(); //make new node ptr to- 
        new_NodePtr->setItem(item);//insert new item
        //Note: ^next & previous are already set to nullptr because of DoubleNode default constructor

        //Case1: Inserting into head of the list && first itemCount on the list 
        if(itemCount_ == 0 && position == 1)
        {
            headPtr_ = new_NodePtr;
            itemCount_++;
        }
        else if(position == 1 && itemCount_ >= 1)//Case1 1.5: Inserting into head of the list && NOT first item in the list 
        {
            new_NodePtr->setNext(headPtr_);//set new item's next ptr to original headptr
            headPtr_->setPrevious(new_NodePtr);//set original headptr's previous to new item
            headPtr_ = new_NodePtr;//set headptr to new item
            itemCount_++;
        }
        else if(position > 1 && position <= itemCount_)//Case 2: Inserting into a position that is not an extremity (i.e nor 1st or last position)
        {
            
            DoubleNode<ItemType>* orig_item = getAtPos(position);//get item at position you're inserting
            new_NodePtr->setPrevious(orig_item->getPrevious());//set previous of the new item with original item's previous 
            orig_item->getPrevious()->setNext(new_NodePtr);//set original item's previous' next to the new item
            new_NodePtr->setNext(orig_item);//set new item's next to original item
            orig_item->setPrevious(new_NodePtr);//set original item's previous to the new item
            itemCount_++;
        }
        else //Case 3: Inserting into rear of the list => itemCount+1
        {
            DoubleNode<ItemType>* orig_item = getAtPos(itemCount_);
            orig_item->setNext(new_NodePtr);//set original item's next to new item
            new_NodePtr->setPrevious(orig_item);//set new item's previous to original item
            itemCount_++;
        }
   }
   return canInsert; //will return false if condition doesn't apply
}//end insert

/**
    Removes node at @param position
    *NOTE: Position 1 is the first position, not 0
    *Pre: position is a valid place within the list
    *Post: @return true if the item at position has been removed from the caller list, otherwise false will be returned
    //Case0: Handles edge case of invalid position parameter
    //Case1: removing only node in list
    //Case2: removing from the end
    //Case3: removing from the beginning
    //Case4: removing from a position that is not an extremity
* */
template <class ItemType>
bool DoublyLinkedList<ItemType>::remove(const int &position)
{
    bool canRemove = !isEmpty() && position >= 1 && position <= itemCount_;//Case 0: list can't be empty & position must be within bounds to remove
    if(canRemove)
    {
        DoubleNode<ItemType>* traversePtr = headPtr_;
        
        if(itemCount_ == 1 && position == 1)//Case 1: removing only node in list
        {
            delete headPtr_;
            headPtr_ = nullptr;
            itemCount_--;
        }
        else if(position == itemCount_)//Case2: removing from the end
        {
            traversePtr = getAtPos(position);
            traversePtr->getPrevious()->setNext(nullptr);//get remove-item's previous & set it to nullptr
            delete traversePtr;//delete remove-item
            itemCount_--;
        }
        else if(position == 1 && itemCount_ > 1)//Case3: removing from the beginning but itemCount_>1
        {
            traversePtr = traversePtr->getNext();//set headptr = headptr's next 
            traversePtr->setPrevious(nullptr);//set the previous of next to nullptr
            delete headPtr_;//deallocate headptr 
            headPtr_ = traversePtr;//set new headptr equal to the next item on the list
            itemCount_--;
        }
        else if(position > 1)//Case4: removing from a position that is not an extremity (i.e all other cases)
        {
            traversePtr = getAtPos(position);
            traversePtr->getPrevious()->setNext(traversePtr->getNext());//get remove-item's previous & set it to remove-item's next item
            traversePtr->getNext()->setPrevious(traversePtr->getPrevious());//get remove-item's next & set it to remove-item's previous
            delete traversePtr;//remove-item from list
            itemCount_--;
        }
    }
    return canRemove;
}//end remove

/** @return true if itemCount_ is 0
*/
template <class ItemType>
bool DoublyLinkedList<ItemType>::isEmpty() const
{

    return itemCount_ == 0;
}//end isEmpty

/**
    Removes all items from the caller list
    Traverse through the linked list and delete each individual node
    @post: no nodes remain in the list and itemCount_ is at 0
*/
template <class ItemType>
void DoublyLinkedList<ItemType>::clear()
{
    DoubleNode<ItemType>* deleteNode_ptr = headPtr_;
    while(headPtr_ != nullptr)//while list isn't empty
    {
        headPtr_ = headPtr_->getNext();//set headptr equal to next item on the list
        deleteNode_ptr->setNext(nullptr);//set the original headptr's next item to nullptr
        delete deleteNode_ptr;//deallocate ptr
        deleteNode_ptr = headPtr_;//set to headPtr which will get the next item on the list to delete
    }
    itemCount_ = 0;//after every item in the list is cleared set itemCount to 0
}//end clear

/** @post Iteratively outputs the contents of the caller list on the console
Example: "A B C D E"
*NOTE: theres no space at the end of display.
*/
template <class ItemType>
void DoublyLinkedList<ItemType>::display() const
{
    DoubleNode<ItemType>* traversePtr = headPtr_;
    if(!isEmpty())
    {
        std::cout << traversePtr->getItem();//print item
        traversePtr = traversePtr->getNext();//set equal to next item on the list
        while(traversePtr != nullptr)
        {
            std::cout<<" "<<traversePtr->getItem();//print next item on list
            traversePtr = traversePtr->getNext();//set = get next item on the list
        }
        std::cout<<std::endl;//when complete => new line no space
    }
    /*
    //FOR TESTING
    std::cout<< "The list contains "<< itemCount_<<" items:" << std::endl;*/
    
}//end display

/** Iteratively @post: outputs the contents of the caller list backwards on the console
Example: if we had A B C D E => we would display "E D C B A"
*/
template <class ItemType>
void DoublyLinkedList<ItemType>::displayBackwards() const
{

    DoubleNode<ItemType>* traversePtr = getAtPos(itemCount_);//set = get tail ptr
    for(int i = itemCount_; i > 0; i--)//starting from end of the list to headptr
    {
        if(i != 1) //Printing backwards goes from tail to headPtr; if it's not the headPtr_ => print item with space
        {
            std::cout << traversePtr->getItem() << " ";
            traversePtr = traversePtr->getPrevious();
        }
        else//if headPtr_ i.e last item on list
        {
            std::cout << traversePtr->getItem() << std::endl;
            traversePtr = traversePtr->getPrevious();//ends for loop   
        }

    }
}//end displayBackwards

/** Reverses the list such that if my list was A B C D 
    @post will now be D C B A
    *NOTE: previous and next pointers are changed
    & testfile tests invert with both display and displayBackwards
*/
template <class ItemType>
void DoublyLinkedList<ItemType>::invert()
{
    if(!isEmpty() && itemCount_>1)
    {
        DoubleNode<ItemType>* currPtr_ = headPtr_;
        DoubleNode<ItemType>* traversePtr = nullptr;
        while(currPtr_ != nullptr)
        {
            currPtr_->setPrevious(currPtr_->getNext());
            currPtr_->setNext(traversePtr);
            traversePtr=currPtr_;
            currPtr_= currPtr_->getPrevious();
        }
        headPtr_=traversePtr;
    }
}//end invert
