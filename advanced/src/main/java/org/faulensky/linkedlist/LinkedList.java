/*
 * Copyright 2014 Plain Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.faulensky.linkedlist;


public class LinkedList<T>
{
    // reference to the head node.
    private Node<T> head;
    private int listCount;

    // LinkedList constructor
    public LinkedList()
    {
        // this is an empty list, so the reference to the head node
        // is set to a new node with no data
        head = new Node<>(null);
        listCount = 0;
    }

    public void add(T data)
    // appends the specified element to the end of this list.
    {
        Node<T> temp = new Node<>(data);
        Node<T> current = head;
        // starting at the head node, crawl to the end of the list
        while(current.getNext() != null)
        {
            current = current.getNext();
        }
        // the last node's "next" reference set to our new node
        current.setNext(temp);
        listCount++;// increment the number of elements variable
    }

    public void add(T data, int index)
    // inserts the specified element at the specified position in this list.
    {
        Node<T> temp = new Node<>(data);
        Node<T> current = head;
        // crawl to the requested index or the last element in the list,
        // whichever comes first
        for(int i = 1; i < index && current.getNext() != null; i++)
        {
            current = current.getNext();
        }
        // set the new node's next-node reference to this node's next-node reference
        temp.setNext(current.getNext());
        // now set this node's next-node reference to the new node
        current.setNext(temp);
        listCount++;// increment the number of elements variable
    }

    public T get(int index)
    // returns the element at the specified position in this list.
    {
        // index must be non-negative
        if(index < 0)
            return null;

        Node<T> current = head.getNext();
        for(int i = 0; i < index; i++)
        {
            if(current.getNext() == null)
                return null;

            current = current.getNext();
        }
        return current.getData();
    }

    public boolean remove(int index)
    // removes the element at the specified position in this list.
    {
        // if the index is out of range, exit
        if(index < 0 || index > size())
            return false;

        Node<T> current = head;
        for(int i = 0; i < index; i++)
        {
            if(current.getNext() == null)
                return false;

            current = current.getNext();
        }
        current.setNext(current.getNext().getNext());
        listCount--; // decrement the number of elements variable
        return true;
    }

    public boolean removeElement(T data) {
        Node<T> current = head;
        // starting at the head node, crawl to the end of the list
        int i=-1;
        while(current.getNext() != null)
        {
            if (current.getData() == data) {
                break;
            }
            current = current.getNext();
            i++;
        }

        return remove(i);
    }

    public int size()
    // returns the number of elements in this list.
    {
        return listCount;
    }

    public String toString()
    {
        Node<T> current = head.getNext();
        String output = "";
        while(current != null)
        {
            output += "[" + current.getData().toString() + "]";
            current = current.getNext();
        }
        return output;
    }

    private class Node<T>
    {
        // reference to the next node in the chain,
        // or null if there isn't one.
        Node<T> next;
        // data carried by this node.
        // could be of any type you need.
        T data;


        // Node constructor
        public Node(T data)
        {
            next = null;
            this.data = data;
        }

        // another Node constructor if we want to
        // specify the node to point to.
        public Node(T data, Node<T> next)
        {
            this.next = next;
            this.data = data;
        }

        // these methods should be self-explanatory
        public T getData()
        {
            return data;
        }

        public void setData(T data)
        {
            this.data = data;
        }

        public Node<T> getNext()
        {
            return next;
        }

        public void setNext(Node<T> next)
        {
            this.next = next;
        }
    }
}
