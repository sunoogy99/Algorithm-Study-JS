# Node.js 베이스 이미지 사용
FROM node:14

# 앱 디렉토리 생성
WORKDIR /usr/src/app

# 패키지 파일 복사
COPY package*.json ./

# 의존성 설치
RUN npm install

# 앱 소스 복사
COPY . .

# JEST 실행
CMD ["npm", "test"]