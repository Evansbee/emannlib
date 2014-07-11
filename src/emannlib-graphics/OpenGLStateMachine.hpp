
	public:
		void BeginDraw(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) const;
		void EndDraw();

		//OGL Control
	public:
		void PushModelView();
		void PopModelView();
		void ModelViewLoadIdentity();
		void Transform(const glm::mat4& matrix);
		void Transform(const GLfloat* matrix);

		void Translate(const glm::vec3& translate);
		void Translate(const glm::vec2& translate);

		void Scale(const glm::vec3& scale);
		void Scale(const glm::vec2& scale);

		void Rotate(float radians, const glm::vec3& normalVector);
		void Rotate(float radians);

		void LookAt(const glm::vec3& point, const glm::vec3& viewer, const glm::vec3& up);

		void PushProjection();
		void PopProjection();
		void Ortho2D(float left, float right, float bottom, float top, float znear = -1.0f, float zfar = 1.0f);
		void Ortho2DFromCenterAndExtents(const Vec2f& center, float newWidth, float newHeight);
		void Perspective(float fovy, float aspect, float znear, float zfar);