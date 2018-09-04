FROM funkyfisch/opencv3-raspbian

LABEL maintainer="Ioannis Gkikas"

RUN mkdir /opt/motion-tracker
COPY . /opt/motion-detector-tracker
WORKDIR /opt/motion-detector-tracker
RUN cmake .
RUN make