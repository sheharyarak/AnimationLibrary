CC:=gcc
EXE:=animate.exe
CFLAGS:=-Wall
OBJS:= Animation.o Sprite.o Drawable.o Canvas.o Main.o
MAGICK:=`Magick++-config --cppflags --cxxflags --ldflags --libs`
THREADS:= -pthread -lpthread

%.o: %.c
     $(CC) $(CFLAGS) $(THREADS) -MD -MP $< -c -o $@

$(EXE): $(OBJS)
    $(CC) $^ $(THREADS) $(MAGICK) -o $@

clean:
    rm -f $(OBJS) $(EXE)

-include $(OBJS:.o=.d)
