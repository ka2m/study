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

package org.faulensky.queue;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Queue<T> {
    private List<T> queue;

    public Queue() {
        queue = new ArrayList<>();
    }

    public Queue(T... elements) {
        queue = new ArrayList<>(Arrays.asList(elements));
    }

    public void add(T element) {
        queue.add(queue.size(), element);
    }

    public T head() {
        return queue.get(0);
    }

    public T peek() {
        T element = queue.get(0);
        queue.remove(0);
        return element;
    }


    public boolean isEmpty() {
        return queue.size() == 0;
    }

    @Override
    public String toString() {
        return queue.toString();
    }
}