CC:=g++
EXE:=animate.exe
CFLAGS:=-Wall
OBJS:= Canvas.o Drawable.o Sprite.o Animation.o WriteImages.o Main.o
MAGICK:=`Magick++-config --cppflags --cxxflags --ldflags --libs`
THREADS:= -pthread -lpthread

%.o: %.cpp
	$(CC) $(CFLAGS) $(THREADS) -MD -MP $< -c -o $@

$(EXE): $(OBJS)
	$(CC) $^ $(THREADS) $(MAGICK) -o $@

clean:
	rm -f $(OBJS) $(EXE)

-include $(OBJS:.o=.d)
