ARG version=bionic
FROM theshadowx/qt5:${version} AS qt

LABEL author = "Sankov Vladimir" mail="v.n.sankov92@mail.ru"

RUN mkdir -p /app/projects

ENV gitUrl=https://github.com/ingener-vladimir/FccSrImitator.git branch=master

WORKDIR /app/projects

EXPOSE 9090

ENTRYPOINT git -C /app/projects clone $gitUrl \
                && cd /app/projects/FccSrImitator \
                && git checkout $branch \
                && qmake /app/projects/FccSrImitator/FccSrImitator.pro \
                && make \
                && cp app/projects/FccSrImitator/bin/debug/ControlStation/ControlStation /app/res/ControlStation
CMD /bin/sh



