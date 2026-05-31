FROM gcc:latest

WORKDIR /app

COPY . .

RUN gcc src/*.c -I include -o /usr/local/bin/atlas

CMD ["atlas"]