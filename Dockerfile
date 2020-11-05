FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc MyOpg.c -o MyOpg
RUN chmod +x MyOpg
