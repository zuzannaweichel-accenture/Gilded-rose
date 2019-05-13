#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>

extern "C" {
#include "GildedRose.h"
}

char* run30Cycles();
char* readTextFile();

TEST_GROUP(TestGildedRoseGroup)
{
  void setup() {
  }
  void teardown() {
  }
};

TEST(TestGildedRoseGroup, FirstTest)
{
  char* actualBuffer = run30Cycles();
  char* expectedBuffer = readTextFile();
  STRCMP_EQUAL(expectedBuffer, actualBuffer);
  free(actualBuffer);
  free(expectedBuffer);
}

int main(int ac, char** av)
{
  return CommandLineTestRunner::RunAllTests(ac, av);
}

char* readTextFile()
{
    char* buffer = 0;
    long length = 0;
    FILE* f = fopen ("GildedRoseUpdate30Days.txt", "rb"); //was "rb"

    if (f)
    {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);
      buffer = (char*)malloc ((length+1)*sizeof(char));
      if (buffer)
      {
        fread (buffer, sizeof(char), length, f);
      }
      fclose (f);
    }
    buffer[length] = '\0';

    return buffer;
}

char* run30Cycles()
{
  Item items[9];
  int last = 0;
  int day;
  int index;
  char* updateBuffer = 0;
  int bufOffset = 0;
  int bufSize = 15000*sizeof(char);
  updateBuffer = (char*)malloc(bufSize);

  init_item(items + last++, "+5 Dexterity Vest", 10, 20);
  init_item(items + last++, "Aged Brie", 2, 0);
  init_item(items + last++, "Elixir of the Mongoose", 5, 7);
  init_item(items + last++, "Sulfuras, Hand of Ragnaros", 0, 80);
  init_item(items + last++, "Sulfuras, Hand of Ragnaros", -1, 80);
  init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 15, 20);
  init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 10, 49);
  init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 5, 49);
  init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 5, 48);

  for (day = 0; day < 30; day++)
  {
      bufOffset += sprintf(updateBuffer+bufOffset, "-------- day %d --------\n", day);
      if (bufOffset >= bufSize) break;
      bufOffset += sprintf(updateBuffer+bufOffset, "name, sellIn, quality\n");
      if (bufOffset >= bufSize) break;
      for(index = 0; index < last; index++) {
          Item* localItem = items + index;
          bufOffset += sprintf(updateBuffer + bufOffset, "%s, %d, %d\n", localItem->name, localItem->sellIn, localItem->quality);
          if (bufOffset >= bufSize) break;
      }
      if (bufOffset >= bufSize) break;
      bufOffset += sprintf(updateBuffer+bufOffset, "\n");

      update_quality(items, last);
      if (bufOffset >= bufSize) break;
  }
  return updateBuffer;
}
