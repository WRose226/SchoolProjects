#Wyatt Rose#
#Project 4 - Getting to Know Ruby#
#This file mimics the behaviour of the Racket cons/pair class#

#constructs a pair
def cons(value1, value2)
    Pair.new(value1, value2)
end

public
#checks if object is pair, returns boolean
def pair?
    self.class == Pair ? true : false
end

class Pair
    $counter
    $string = "("
    @@newList

    #initializes the pair
    #   value1 - first pair value
    #   value2 - second pair value
    def initialize(value1, value2)
        @value1 = value1
        @value2 = value2
    end

    #returns first value of pair
    def car
        return @value1
    end

    #returns second value of pair
    def cdr
        return @value2
    end

    #creates null pair
    def self.null
        return nil
    end

    #returns string of pair/list
    def to_s

        $string = "("
        to_sHelper
    end

    #recursive logic for to_s
    def to_sHelper

        if car.class == Pair
            $string += "("
            car.to_sHelper
        elsif car.nil?
            $string += "()"
        else 
            $string += "#{car}"
        end

        if cdr.class == Pair
            $string += " "
            cdr.to_sHelper
        elsif cdr.nil?
            $string += ")"
        else
            $string += " . #{cdr})"
        end
    end

    #returns boolean if list
    def list?

        return true if cdr.nil?

        cdr.class == Pair ? cdr.list? : false
    end
    
    #counts number of objects in list
    def count

        return false unless list?

        $counter = 0

        countHelper
    end

    #Recursive logic for count function
    def countHelper

        $counter += 1 unless car.nil?

        cdr.nil? ? $counter : cdr.countHelper
    end

    #appends other to self
    def append(other)

        return false unless self.list?

        @@newList = self

        appendHelper(other, @@newList)

        return @@newList
    end

    #recursive logic for append
    def appendHelper(other, newList)
        @thiscar = car
        
        cdr.appendHelper(other, @@newList) unless cdr.class != Pair

        if cdr.nil?
            @@newList = cons(@thiscar, other)
        else
            @@newList = cons(@thiscar, @@newList)
        end
    end

    #checks if null
    def null?
        list? && car.nil? ? true : false
    end

end
    