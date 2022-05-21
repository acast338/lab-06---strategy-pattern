#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
#include "spreadsheet.hpp"
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

class Select_Contains : public Select_Column
{
private:
        std::string search;
public:
        Select_Contains(const Spreadsheet* sheet,const  std::string& col,const std::string& stringToMatch) : Select_Column(sheet, col), search(stringToMatch) {}

        bool select(const std::string& stringToMatch) const
        {
                if (stringToMatch.find(search) != std::string::npos)
                {
                        return 1;
                }
                return 0;
        }
};


class Select_Not: public Select
{
private:
  Select* strat;
public:
  ~Select_Not() {delete strat; }
  Select_Not(Select* strategy) {strat = strategy; }
    bool select(const Spreadsheet* sheet, int row)const{
   return !strat->select(sheet, row);
  }
};

class Select_Or : public Select
{
private:
	Select* strat1;
	Select* strat2;
public:
	~Select_Or() { delete strat1; delete strat2; }
	Select_Or(Select* strategy1, Select* strategy2)
	{
		strat1 = strategy1;
		strat2 = strategy2;
	}

	bool select(const Spreadsheet* sheet, int row) const
	{
		return strat1->select(sheet, row) || strat2->select(sheet, row);
	}
};

class Select_And : public Select
{
private:
	Select* strat1;
	Select* strat2;
public:
	~Select_And() { delete strat1; delete strat2; }
	Select_And(Select* strategy1, Select* strategy2)
	{
		strat1 = strategy1;
		strat2 = strategy2;
	}

	bool select(const Spreadsheet* sheet, int row) const
	{
		return (strat1->select(sheet, row) && strat2->select(sheet, row));
	}
};
#endif //__SELECT_HPP__
