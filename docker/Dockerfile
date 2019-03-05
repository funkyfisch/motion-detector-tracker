FROM funkyfisch/opencv3-raspbian
<<<<<<< Updated upstream

LABEL maintainer="Ioannis Gkikas"

RUN mkdir /opt/motion-tracker
COPY . /opt/motion-detector-tracker
WORKDIR /opt/motion-detector-tracker
RUN cmake .
RUN make
=======
RUN mkdir /opt/motion-tracker
COPY . /opt/motion-tracker
WORKDIR /opt/motion-tracker
RUN cmake .
RUN make
>>>>>>> Stashed changes
