#include "select.hpp"

#include "gtest/gtest.h"

Spreadsheet* sheet = new Spreadsheet();

TEST(Select_Contains, inSheet){
	sheet->set_column_names({"First", "Last", "Age", "Major" });
	sheet->add_row({"Amanda", "Andrews", "22", "business" });
	Select* select = new Select_Contains(sheet, "Last", "Andrews");
	ASSERT_TRUE(select->select(sheet, 0));
	delete select;
}


TEST(Select_Contains, notInSheet){
	Select* select = new Select_Contains(sheet, "Last", "Smith");
        ASSERT_FALSE(select->select(sheet, 0));
        delete select;
}

TEST(Select_Contains, emptySearch){
        Select* select = new Select_Contains(sheet, "Last", "");
        ASSERT_TRUE(select->select(sheet, 0));
        delete select;
}

TEST(Select_Contains, multipleMatches){
        sheet->add_row({"Brian", "Becker", "21", "computer science" });
        Select* select = new Select_Contains(sheet, "Last", "e");
        ASSERT_TRUE(select->select(sheet, 0));
	ASSERT_TRUE(select->select(sheet, 1));
        delete select;
}

TEST(Select_Not, inSheet){
        Select* select = new Select_Not(new Select_Contains(sheet, "Last", "Andrews"));
        ASSERT_FALSE(select->select(sheet, 0));
        delete select;
}

TEST(Select_Not, notInSheet){
        Select* select = new Select_Not(new Select_Contains(sheet, "Last", "Jobs"));
        ASSERT_TRUE(select->select(sheet, 0));
        delete select;
}

TEST(Select_Or, bothTrue){
        Select* select = new Select_Or(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Amanda"));
        ASSERT_TRUE(select->select(sheet, 0));
        delete select;
}

TEST(Select_Or, bothFalse){
        Select* select = new Select_Or(new Select_Contains(sheet, "Last", "Jobs"), new Select_Contains(sheet, "First", "Steve"));
        ASSERT_FALSE(select->select(sheet, 0));
        delete select;
}

TEST(Select_Or, oneTrueOneFalse){
        Select* select = new Select_Or(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Steve"));
        ASSERT_TRUE(select->select(sheet, 0));
        delete select;
}

TEST(Select_And, bothTrue){
	Select* select = new Select_And(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Amanda"));
	ASSERT_TRUE(select->select(sheet, 0));
        delete select;
}

TEST(Select_And, bothFalse){
        Select* select = new Select_And(new Select_Contains(sheet, "Last", "Jobs"), new Select_Contains(sheet, "First", "Stve"));
        ASSERT_FALSE(select->select(sheet, 0));
        delete select;
}

TEST(Select_And, oneTrueOneFalse){
        Select* select = new Select_And(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Steve"));
        ASSERT_FALSE(select->select(sheet, 0));
        delete select;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv); 
  return RUN_ALL_TESTS();
}
