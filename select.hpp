#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains : public Select_Column {
  private:
    std::string input;
  public:
    Select_Contains(const Spreadsheet* sheet_, const std::string& name, const std::string& s): Select_Column(sheet_, name){
        input = s;
    }

    virtual bool select (const std::string& s) const{
        bool isFound = false;
        int index;
        //for(int i = 0; i < s.size(); ++i){
            if(index = s.find(s.begin(), s.end(), input) != std::string::npos){
                isFound = true;
            }
        //}
        return isFound;
    }
};

/*
class Select_Not : public Select {
};
class Select_And : public Select {
};
class Select_Or : public Select {
};
*/
#endif //__SELECT_HPP__
